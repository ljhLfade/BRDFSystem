/*
 *
 * Demonstrates how to load and display an Wavefront OBJ file. 
 * Using triangles and normals as static object. No texture mapping.
 *
 * OBJ files must be triangulated!!!
 * Non triangulated objects wont work!
 * You can use Blender to triangulate
 *
 */
#include "stdafx.h"
#include "glut_obj.h"

#include <windows.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#include <GL/glut.h>
#include "glut.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

 
Model_OBJ::Model_OBJ()
{
	this->TotalConnectedTriangles = 0; 
	this->TotalConnectedPoints = 0;
}
 
float* Model_OBJ::calculateNormal( float *coord1, float *coord2, float *coord3 )
{
   /* calculate Vector1 and Vector2 */
   float va[3], vb[3], vr[3], val;
   va[0] = coord1[0] - coord2[0];
   va[1] = coord1[1] - coord2[1];
   va[2] = coord1[2] - coord2[2];
 
   vb[0] = coord1[0] - coord3[0];
   vb[1] = coord1[1] - coord3[1];
   vb[2] = coord1[2] - coord3[2];
 
   /* cross product */
   vr[0] = va[1] * vb[2] - vb[1] * va[2];
   vr[1] = vb[0] * va[2] - va[0] * vb[2];
   vr[2] = va[0] * vb[1] - vb[0] * va[1];
 
   /* normalization factor */
   val = sqrt( vr[0]*vr[0] + vr[1]*vr[1] + vr[2]*vr[2] );
 
	float norm[3];
	norm[0] = vr[0]/val;
	norm[1] = vr[1]/val;
	norm[2] = vr[2]/val;
 
 
	return norm;
}

float* Model_OBJ::normalize(float v1, float v2, float v3)
{
	float norm[3], val;
	
	val = sqrt(v1*v1 + v2*v2 + v3*v3);
	norm[0] = v1/val;
	norm[1] = v2/val;
	norm[2] = v3/val;

	return norm;
}
 
void Model_OBJ::calculateSize()
{
	
	for(int i = 0; i<TotalConnectedPoints; i = i+3)
	{
		float tx = Vertex_Buffer[i] ;
		if (tx<size.left)
			size.left = tx;
		if (tx>size.right)
			size.right = tx;
		float ty = Vertex_Buffer[i+1];
		if (ty<size.down)
			size.down = ty;
		if (ty>size.up)
			size.up = ty;
		float tz = Vertex_Buffer[i+2];
		if (tz<size.back)
			size.back = tz;
		if (tz>size.front)
			size.front = tz;
	}

	size.centerx = (size.left+size.right)/2;
	size.centery = (size.up +size.down)/2;
	size.centerz = (size.front + size.back)/2;

	size.width   = abs(size.right-size.left);
	size.hight   = abs(size.up - size.down);
}
 
int Model_OBJ::Load(char* filename)
{
	string line;
	ifstream objFile (filename);	
	if (objFile.is_open())													// If obj file is open, continue
	{
		objFile.seekg (0, ios::end);										// Go to end of the file, 
		long fileSize = objFile.tellg();									// get file size
		objFile.seekg (0, ios::beg);										// we'll use this to register memory for our 3d model
 
		Vertex_Buffer = (float*) malloc (fileSize);							// Allocate memory for the verteces
		Faces_Triangles = (float*) malloc(fileSize*sizeof(float));			// Allocate memory for the triangles
		Faces_Normals  = (float*) malloc(fileSize*sizeof(float));					// Allocate memory for the normals
		Triangles = (int*) malloc(fileSize*sizeof(int));
		Vertex_Normals = (float*) malloc(fileSize*sizeof(float));
 
		int triangle_index = 0;												// Set triangle index to zero
		int normal_index = 0;												// Set normal index to zero
		int cnt = 0;
 
		while (! objFile.eof() )											// Start reading file data
		{		
			getline (objFile,line);											// Get line from file
 
			if (line.c_str()[0] == 'v')										// The first character is a v: on this line is a vertex stored.
			{
				line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf
 
				sscanf(line.c_str(),"%f %f %f ",							// Read floats from the line: v X Y Z
					&Vertex_Buffer[TotalConnectedPoints],
					&Vertex_Buffer[TotalConnectedPoints+1], 
					&Vertex_Buffer[TotalConnectedPoints+2]);
 
				float* norm;
				norm = normalize(Vertex_Buffer[TotalConnectedPoints+0], Vertex_Buffer[TotalConnectedPoints+0], Vertex_Buffer[TotalConnectedPoints+0]);
				Vertex_Normals[TotalConnectedPoints+0] = norm[0];
				Vertex_Normals[TotalConnectedPoints+1] = norm[1];
				Vertex_Normals[TotalConnectedPoints+2] = norm[2];
		
				TotalConnectedPoints += POINTS_PER_VERTEX;					// Add 3 to the total connected points
			}
			if (line.c_str()[0] == 'f')										// The first character is an 'f': on this line is a point stored
			{
		    	line[0] = ' ';												// Set first character to 0. This will allow us to use sscanf
 
				int vertexNumber[4] = { 0, 0, 0 };
                sscanf(line.c_str(),"%i%i%i",								// Read integers from the line:  f 1 2 3
					&vertexNumber[0],										// First point of our triangle. This is an 
					&vertexNumber[1],										// pointer to our vertexBuffer list
					&vertexNumber[2] );										// each point represents an X,Y,Z.
 
				vertexNumber[0] -= 1;										// OBJ file starts counting from 1
				vertexNumber[1] -= 1;										// OBJ file starts counting from 1
				vertexNumber[2] -= 1;										// OBJ file starts counting from 1
					
				Triangles[cnt*3+0] = vertexNumber[0];
				Triangles[cnt*3+1] = vertexNumber[1];
				Triangles[cnt*3+2] = vertexNumber[2];
				cnt++;
 
				/********************************************************************
				 * Create triangles (f 1 2 3) from points: (v X Y Z) (v X Y Z) (v X Y Z). 
				 * The vertexBuffer contains all verteces
				 * The triangles will be created using the verteces we read previously
				 */
 
				int tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++)					
				{
					Faces_Triangles[triangle_index + tCounter   ] = Vertex_Buffer[3*vertexNumber[i] ];
					Faces_Triangles[triangle_index + tCounter +1 ] = Vertex_Buffer[3*vertexNumber[i]+1 ];
					Faces_Triangles[triangle_index + tCounter +2 ] = Vertex_Buffer[3*vertexNumber[i]+2 ];
					tCounter += POINTS_PER_VERTEX;
				}
 
				/*********************************************************************
				 * Calculate all normals, used for lighting
				 */ 
				float coord1[3] = { Faces_Triangles[triangle_index], Faces_Triangles[triangle_index+1],Faces_Triangles[triangle_index+2]};
				float coord2[3] = {Faces_Triangles[triangle_index+3],Faces_Triangles[triangle_index+4],Faces_Triangles[triangle_index+5]};
				float coord3[3] = {Faces_Triangles[triangle_index+6],Faces_Triangles[triangle_index+7],Faces_Triangles[triangle_index+8]};
				float *norm = this->calculateNormal( coord1, coord2, coord3 );
 
				tCounter = 0;
				for (int i = 0; i < POINTS_PER_VERTEX; i++)
				{
					Faces_Normals[normal_index + tCounter ] = norm[0];
					Faces_Normals[normal_index + tCounter +1] = norm[1];
					Faces_Normals[normal_index + tCounter +2] = norm[2];
					tCounter += POINTS_PER_VERTEX;
				}
 
				triangle_index += TOTAL_FLOATS_IN_TRIANGLE;
				normal_index += TOTAL_FLOATS_IN_TRIANGLE;
				TotalConnectedTriangles += TOTAL_FLOATS_IN_TRIANGLE;			
			}	
		}

		TotalFaces = cnt;
		objFile.close();														// Close OBJ file
	}
	else 
	{
		cout << "Unable to open file";								
	}
	return 0;
}
 
void Model_OBJ::Release()
{
	free(this->Faces_Triangles);
	free(this->Faces_Normals);
	free(this->Vertex_Buffer);
	free(this->Triangles);
}
 
void Model_OBJ::Draw()
{
 	glEnableClientState(GL_VERTEX_ARRAY);						// Enable vertex arrays
 	glEnableClientState(GL_NORMAL_ARRAY);						// Enable normal arrays
	glVertexPointer(3,GL_FLOAT,	0,Faces_Triangles);				// Vertex Pointer to triangle array
	glNormalPointer(GL_FLOAT, 0, Faces_Normals);						// Normal pointer to normal array
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);		// Draw the triangles
	glDisableClientState(GL_VERTEX_ARRAY);						// Disable vertex arrays
	glDisableClientState(GL_NORMAL_ARRAY);						// Disable normal arrays
}