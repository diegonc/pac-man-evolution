#!/bin/sh

SCRIPT_DIR=`dirname $0`
TOP_DIR=`cd $SCRIPT_DIR; pwd`

COMMON_HEADERS="`cd $TOP_DIR/common/common; ls *.h`"
SERVER_HEADERS="`cd $TOP_DIR/common/server; ls *.h`"
EDITOR_HEADERS="`cd $TOP_DIR/common/editor; ls *.h`"

for i in $COMMON_HEADERS; do
    for j in `ls *.{cpp,h}`; do
	echo -n "Buscando $i en $j..."
	if egrep -q "#include[ \t]+\"\.\.\/.*\/$i\"" $j; then
	    SED_PAT="s/" # comando
	    SED_PAT="$SED_PAT#include\([[:space]]+\)\"\.\.\/.*\/$i\"/" # busca
	    SED_PAT="$SED_PAT#include\1<common\/$i>/"; # reemplaza
	    sed -i -e $SED_PAT $j
	    echo "reemplazado."
	elif egrep -q "#include[ \t]+\"$i\""; then
	    SED_PAT="s/" # comando
	    SED_PAT="$SED_PAT#include\([[:space]]+\)\"$i\"/" # busca
	    SED_PAT="$SED_PAT#include\1<common\/$i>/"; # reemplaza
	    sed -i -e $SED_PAT $j
	    echo "reemplazado."
	else
	    echo "no encontrado."
	fi
    done
done

for i in $SERVER_HEADERS; do
    for j in `ls *.{cpp,h}`; do
	echo -n "Buscando $i en $j..."
	if egrep -q "#include[ \t]+\"\.\.\/.*\/$i\"" $j; then
	    SED_PAT="s/" # comando
	    SED_PAT="$SED_PAT#include\([[:space]]+\)\"\.\.\/.*\/$i\"/" # busca
	    SED_PAT="$SED_PAT#include\1<server\/$i>/"; # reemplaza
	    sed -i -e $SED_PAT $j
	    echo "reemplazado."
	elif egrep -q "#include[ \t]+\"$i\""; then
	    SED_PAT="s/" # comando
	    SED_PAT="$SED_PAT#include\([[:space]]+\)\"$i\"/" # busca
	    SED_PAT="$SED_PAT#include\1<server\/$i>/"; # reemplaza
	    sed -i -e $SED_PAT $j
	    echo "reemplazado."
	else
	    echo "no encontrado."
	fi
    done
done

for i in $EDITOR_HEADERS; do
    for j in `ls *.{cpp,h}`; do
	echo -n "Buscando $i en $j..."
	if egrep -q "#include[ \t]+\"\.\.\/.*\/$i\"" $j; then
	    SED_PAT="s/" # comando
	    SED_PAT="$SED_PAT#include\([[:space]]+\)\"\.\.\/.*\/$i\"/" # busca
	    SED_PAT="$SED_PAT#include\1<editor\/$i>/"; # reemplaza
	    sed -i -e $SED_PAT $j
	    echo "reemplazado."
	elif egrep -q "#include[ \t]+\"$i\""; then
	    SED_PAT="s/" # comando
	    SED_PAT="$SED_PAT#include\([[:space]]+\)\"$i\"/" # busca
	    SED_PAT="$SED_PAT#include\1<editor\/$i>/"; # reemplaza
	    sed -i -e $SED_PAT $j
	    echo "reemplazado."
	else
	    echo "no encontrado."
	fi
    done
done
