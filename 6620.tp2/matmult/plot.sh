#!/bin/sh

SRC_DIR=$1

if [ ! -d "${SRC_DIR}" ]; then
	echo "Carpeta de corridas ( $1 ) inexistente."
	exit
fi

CWD=`pwd`

cd ${SRC_DIR}

TIMINGS=*.salida

print_plots()
{
	PLOTS_LINE=""
	for i in ${TIMINGS}; do
		PLOT=`basename ${i} .salida`
		PLOTS_LINE="'${PLOT}.data' using 1:2 t \"${PLOT}\" with lines, "${PLOTS_LINE}
	done

	cat | sed -e 's/, $//'  << EOFmark
${PLOTS_LINE}
EOFmark

}

for i in ${TIMINGS}; do
	perl -ne 'if (/Tam:\s+(\S+).*s:\s+(\S+)/) {print "$1 $2\n";}' ${i} > `basename ${i} .salida`.data
done

cat | gnuplot - << EOF
set term latex
set output ${CWD}/${SRC_DIR}-plot.tex
set xlabel 'Dimension'
set ylabel 'Mflop/s'
set key default
set grid
plot `print_plots`

EOF

cd $CWD
