#!/bin/sh

COMMON_H="`cd common/common; ls *.h`"
EDITOR_H="`cd common/editor; ls *.h`"
SERVER_H="`cd common/server; ls *.h`"
DIRS="pme-client common/common common/editor common/server"

cat > fix-headers.sh << EOF
#!/bin/sh

COMMON_H="$COMMON_H"
EDITOR_H="$EDITOR_H"
SERVER_H="$SERVER_H"


EOF

for i in $DIRS; do
	grep "\#include" $i/*.{cpp,h} | awk -f sed_calls.awk
done

cat >> fix-headers.sh << EOF
sed -i -e 's/"\.\.\/server\/KeyOp.h"/<pme-server\/KeyOp.h>/' common/server/PaqueteTeclaCommon.cpp
sed -i -e 's/"\.\.\/server\/KeyOp.h"/<pme-server\/KeyOp.h>/' pme-client/AplicacionGrafica.h

EOF

chmod +x fix-headers.sh