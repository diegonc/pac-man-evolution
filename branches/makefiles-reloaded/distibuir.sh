#!/bin/sh

EDITOR_FILES="
bif_este.cpp
bif_este.h
bif_norte.cpp
bif_norte.h
bif_oeste.cpp
bif_oeste.h
bif_sur.cpp
bif_sur.h
bonus.cpp
bonus.h
casa_este.cpp
casa_este.h
casa_fantasmas.cpp
casa_fantasmas.h
casa_norte.cpp
casa_norte.h
casa_oeste.cpp
casa_oeste.h
casa_sur.cpp
casa_sur.h
casillero.cpp
casillero.h
componente.cpp
componente.h
cruce.cpp
cruce.h
dato_vertice.cpp
dato_vertice.h
definiciones.h
elemento.cpp
elemento.h
esq_este.cpp
esq_este.h
esq_norte.cpp
esq_norte.h
esq_oeste.cpp
esq_oeste.h
esq_sur.cpp
esq_sur.h
estructural.cpp
estructural.h
fab_elementos.cpp
fab_elementos.h
mapa.cpp
mapa.h
modelo.cpp
modelo.h
modificador.cpp
modificador.h
mundo.cpp
mundo.h
nivel.cpp
nivel.h
obj_nulo.h
pas_horiz.cpp
pas_horiz.h
pas_vert.cpp
pas_vert.h
portal.cpp
portal.h
portal_este.cpp
portal_este.h
portal_norte.cpp
portal_norte.h
portal_oeste.cpp
portal_oeste.h
portal_sur.cpp
portal_sur.h
power_up.cpp
power_up.h
punto.cpp
punto.h
recorredor_grafo.h
salida.cpp
salida.h"

COMMON_FILES="
arco.h
bloqueo.cpp
bloqueo.h
client_socket.cpp
client_socket.h
comparador.h
contador.h
errores.cpp
errores.h
evento.cpp
evento.h
grafo.h
mutex.cpp
mutex.h
observable.cpp
observable.h
observador.h
server_socket.cpp
server_socket.h
smart_pointer.h
smart_pointer_arrays.h
socket.cpp
socket.h
thread.cpp
thread.h
vertice.h
wrapper.h
Configuracion.cpp
Configuracion.h
ConfValue.cpp
ConfValue.h
"
SERVER_FILES="
BufferReader.h
Cliente.cpp
Cliente.h
Comestible.cpp
Comestible.h
ComestibleFactory.cpp
ComestibleFactory.h
ComparadorPosicion.h
Direccion.cpp
Direccion.h
EscritorCliente.cpp
EscritorCliente.h
EscuchadorCliente.cpp
EscuchadorCliente.h
EstructuralCasaFantasma.cpp
EstructuralCasaFantasma.h
EstructuralPasillo.cpp
EstructuralPasillo.h
EstructuralUnitario.cpp
EstructuralUnitario.h
EstructuralUnitarioFactory.cpp
EstructuralUnitarioFactory.h
Fantasma.cpp
Fantasma.h
Frutita.h
InputBitStream.cpp
InputBitStream.h
Jugador.cpp
Jugador.h
MapImpSet.cpp
MapImpSet.h
MapaBajoNivel.h
MemoryReader.cpp
MemoryReader.h
ModeloCommon.cpp
ModeloCommon.h
MundoBajoNivel.h
MundoBasicImp.cpp
MundoBasicImp.h
NovedadComestible.cpp
NovedadComestible.h
Operacion.h
OperacionNula.h
OutputBitStream.cpp
OutputBitStream.h
PacMan.cpp
PacMan.h
Paquete.cpp
Paquete.h
PaqueteInitCommon.cpp
PaqueteInitCommon.h
PaqueteMensaje.cpp
PaqueteMensaje.h
PaqueteQuit.cpp
PaqueteQuit.h
PaqueteStartCommon.cpp
PaqueteStartCommon.h
PaqueteStatusCommon.cpp
PaqueteStatusCommon.h
PaqueteStop.cpp
PaqueteStop.h
PaqueteTeclaCommon.cpp
PaqueteTeclaCommon.h
Personaje.cpp
Personaje.h
Posicion.cpp
Posicion.h
PowerUp.cpp
PowerUp.h
Quesito.h
SocketReader.cpp
SocketReader.h
"

for i in $EDITOR_FILES; do
	svn mv map_editor/$i common/editor/$i
done

for i in $COMMON_FILES; do
	svn mv common/$i common/common/$i
done

for i in $SERVER_FILES; do
	svn mv common/$i common/server/$i
done

svn mv client pme-client
svn mv server pme-server

START_DIR=`pwd`
DIRS="pme-client pme-server map_editor common/editor common/server"

for i in $DIRS; do
	cd $i
	$START_DIR/translate-include.sh
	cd $START_DIR
done

sed -e 's/"\.\.\/server\/KeyOp.h"/<pme-server/KeyOp.h>/' common/server/PaqueteTeclaCommon.cpp
sed -e 's/"\.\.\/server\/KeyOp.h"/<pme-server/KeyOp.h>/' pme-client/AplicacionGrafica.h


