#!/bin/sh

SRC_DIR=$1
DST_DIR=$2

if [ -z "${DST_DIR}" ]; then
	DST_DIR=.
fi

DST_DIR=`cd ${DST_DIR}; pwd`

if [ ! -d "${SRC_DIR}" ]; then
	echo "Carpeta de corridas ( $1 ) inexistente."
	exit
fi

CWD=`pwd`

cd "${SRC_DIR}"

TIMINGS=*.salida

print_plots()
{
	PLOTS_LINE=""
	for i in ${TIMINGS}; do
		PLOT=`basename ${i} .salida`
		PLOTS_LINE="'${PLOT}.data' using 1:2 t \"${PLOT}\" with lines, "${PLOTS_LINE}
	done

	sed -e 's/, $//' << EOFmark
${PLOTS_LINE}
EOFmark

}

for i in ${TIMINGS}; do
	perl -ne 'if (/Tam:\s+(\S+).*s:\s+(\S+)/) {print "$1 $2\n";}' ${i} > `basename ${i} .salida`.data
	sed -i -e 's/\\\\$//' `basename ${i} .salida`.data
done

gnuplot -persist - << EOF
set term png
set output "${DST_DIR}/${SRC_DIR}-plot.png"
set xlabel 'Dimension'
set ylabel 'Mflop/s'
set key default
set grid
plot `print_plots`

EOF

cd $CWD