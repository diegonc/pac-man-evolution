/*
 * ---------------- www.spacesimulator.net --------------
 *   ---- Space simulators and 3d engine tutorials ----
 *
 * Author: Damiano Vitulli <info@spacesimulator.net>
 *
 * ALL RIGHTS RESERVED
 *
 *
 * Tutorial 4: 3d engine - 3ds models loader
 *
 * Include File: 3dsloader.cpp
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <fstream>
//#include <conio.h>
//#include <io.h>
#include "ObjetoVisual.h"
#include "3dsloader.h"




/**********************************************************
 *
 * FUNCTION Load3DS (obj_type_ptr, char *)
 *
 * This function loads a mesh from a 3ds file.
 * Please note that we are loading only the vertices, polygons and mapping lists.
 * If you need to load meshes with advanced features as for example:
 * multi objects, materials, lights and so on, you must insert other chunk parsers.
 *
 *********************************************************/


char Load3DS (ObjetoVisual* Objeto,const char *p_filename)
{
    int i; //Index variable

	FILE *l_file; //File pointer

	unsigned short l_chunk_id; //Chunk identifier
	unsigned int l_chunk_lenght; //Chunk lenght

	unsigned char l_char; //Char variable
	unsigned short l_qty; //Number of elements in each chunk

	unsigned short l_face_flags; //Flag that stores some face information
	obj_type_ptr pFigActual=0;

//    printf("%s",p_filename);
	if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file


	fseek(l_file,0l,SEEK_END);
    long tamanio=ftell(l_file);
    fseek(l_file,0l,SEEK_SET);

    //fclose(l_file);

    //if ((l_file=fopen (p_filename, "rb"))== NULL) return 0; //Open the file

	while (ftell (l_file) < tamanio) //Loop to scan the whole file
	//while (ftell (l_file) < stat(fileno (l_file))) //Loop to scan the whole file
	{
		//getche(); //Insert this command for debug (to wait for keypress for each chuck reading)

		fread (&l_chunk_id, 2, 1, l_file); //Read the chunk header
	//	printf("ChunkID: %x\n",l_chunk_id);
		fread (&l_chunk_lenght, 4, 1, l_file); //Read the lenght of the chunk
		//printf("ChunkLenght: %x\n",l_chunk_lenght);

		switch (l_chunk_id)
        {
			//----------------- MAIN3DS -----------------
			// Description: Main chunk, contains all the other chunks
			// Chunk ID: 4d4d
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4d4d:
			break;

			//----------------- EDIT3DS -----------------
			// Description: 3D Editor chunk, objects layout info
			// Chunk ID: 3d3d (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x3d3d:
			break;

			//--------------- EDIT_OBJECT ---------------
			// Description: Object block, info for each object
			// Chunk ID: 4000 (hex)
			// Chunk Lenght: len(object name) + sub chunks
			//-------------------------------------------
			case 0x4000:
				i=0;
				char nombre[20];
				do
				{
					fread (&l_char, 1, 1, l_file);
                    nombre[i]=l_char;

					i++;
                }while(l_char != '\0' && i<20);

                if (pFigActual){
                    Objeto->Figuras.push_back(pFigActual);
                    pFigActual=new obj_type;
                }else{
                    pFigActual=new obj_type;
                }

                i=0;
                do
				{
					l_char=nombre[i];
					pFigActual->name[i]=l_char;

					i++;
                }while(l_char != '\0' && i<20);

                std::cout << nombre << "\n";


			break;

			//--------------- OBJ_TRIMESH ---------------
			// Description: Triangular mesh, contains chunks for 3d mesh info
			// Chunk ID: 4100 (hex)
			// Chunk Lenght: 0 + sub chunks
			//-------------------------------------------
			case 0x4100:
			break;

			//--------------- TRI_VERTEXL ---------------
			// Description: Vertices list
			// Chunk ID: 4110 (hex)
			// Chunk Lenght: 1 x unsigned short (number of vertices)
			//             + 3 x float (vertex coordinates) x (number of vertices)
			//             + sub chunks
			//-------------------------------------------
			case 0x4110:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                pFigActual->vertices_qty = l_qty;
          //      printf("Number of vertices: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&pFigActual->vertex[i].x, sizeof(float), 1, l_file);
 			//		printf("Vertices list x: %f\n",pFigActual->vertex[i].x);
                    fread (&pFigActual->vertex[i].y, sizeof(float), 1, l_file);
 				//	printf("Vertices list y: %f\n",pFigActual->vertex[i].y);
					fread (&pFigActual->vertex[i].z, sizeof(float), 1, l_file);
 					//printf("Vertices list z: %f\n",pFigActual->vertex[i].z);
				}
				break;

			//--------------- TRI_FACEL1 ----------------
			// Description: Polygons (faces) list
			// Chunk ID: 4120 (hex)
			// Chunk Lenght: 1 x unsigned short (number of polygons)
			//             + 3 x unsigned short (polygon points) x (number of polygons)
			//             + sub chunks
			//-------------------------------------------
			case 0x4120:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
                pFigActual->polygons_qty = l_qty;
                //printf("Number of polygons: %d\n",l_qty);
                for (i=0; i<l_qty; i++)
                {
					fread (&pFigActual->polygon[i].a, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point a: %d\n",pFigActual->polygon[i].a);
					fread (&pFigActual->polygon[i].b, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point b: %d\n",pFigActual->polygon[i].b);
					fread (&pFigActual->polygon[i].c, sizeof (unsigned short), 1, l_file);
					//printf("Polygon point c: %d\n",pFigActual->polygon[i].c);
					fread (&l_face_flags, sizeof (unsigned short), 1, l_file);
					//printf("Face flags: %x\n",l_face_flags);
				}
                break;

			//------------- TRI_MAPPINGCOORS ------------
			// Description: Vertices list
			// Chunk ID: 4140 (hex)
			// Chunk Lenght: 1 x unsigned short (number of mapping points)
			//             + 2 x float (mapping coordinates) x (number of mapping points)
			//             + sub chunks
			//-------------------------------------------
			case 0x4140:
                fread (&l_qty, sizeof (unsigned short), 1, l_file);
				for (i=0; i<l_qty; i++)
				{
					fread (&pFigActual->mapcoord[i].u, sizeof (float), 1, l_file);
					//printf("Mapping list u: %f\n",pFigActual->mapcoord[i].u);
                    fread (&pFigActual->mapcoord[i].v, sizeof (float), 1, l_file);
					//printf("Mapping list v: %f\n",pFigActual->mapcoord[i].v);
				}
                break;

			//----------- Skip unknow chunks ------------
			//We need to skip all the chunks that currently we don't use
			//We use the chunk lenght information to set the file pointer
			//to the same level next chunk
			//-------------------------------------------
			default:
				 fseek(l_file, l_chunk_lenght-6, SEEK_CUR);
        }
	}
	fclose (l_file); // Closes the file stream
	if (pFigActual){
        Objeto->Figuras.push_back(pFigActual);
	}

	std::cout << p_filename << "\n";
	return (1); // Returns ok
}
