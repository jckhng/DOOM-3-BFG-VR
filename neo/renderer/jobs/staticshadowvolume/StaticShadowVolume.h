/*
===========================================================================

Doom 3 BFG Edition GPL Source Code
Copyright (C) 1993-2012 id Software LLC, a ZeniMax Media company.

This file is part of the Doom 3 BFG Edition GPL Source Code ("Doom 3 BFG Edition Source Code").

Doom 3 BFG Edition Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Doom 3 BFG Edition Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Doom 3 BFG Edition Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the Doom 3 BFG Edition Source Code is also subject to certain additional terms. You should have received a copy of these additional terms immediately following the terms and conditions of the GNU General Public License which accompanied the Doom 3 BFG Edition Source Code.  If not, please request a copy in writing from id Software at the address below.

If you have questions concerning this license or the applicable additional terms, you may contact in writing id Software LLC, c/o ZeniMax Media Inc., Suite 120, Rockville, Maryland 20850 USA.

===========================================================================
*/
#ifndef __STATICSHADOWVOLUME_H__
#define __STATICSHADOWVOLUME_H__

/*
================================================================================================

Static Shadow Volume Setup

A static shadow is cast from a static model touching a static light.
A static shadow volume extends to infinity which allows the end caps to be omitted
when the view is outside and far enough away from the shadow volume.

A static shadow volume is created at map load time and this job determines whether or
not the end caps need to be rendered, whether or not the shadow volume needs to be
rendered with Z-Fail, and optionally calculates the shadow volume depth bounds.

================================================================================================
*/

/*
================================================
staticShadowVolumeParms_t
================================================
*/
struct staticShadowVolumeParms_t
{
	// input
	const idShadowVert* 			verts;					// streamed in from main memory
	int								numVerts;
	const triIndex_t* 				indexes;				// streamed in from main memory
	int								numIndexes;
	int								numShadowIndicesWithCaps;
	int								numShadowIndicesNoCaps;
	idBounds						triangleBounds;
	idRenderMatrix					triangleMVP;
	idVec3							localLightOrigin;
	idVec3							localViewOrigin;
	float							zNear;
	float							lightZMin;
	float							lightZMax;
	bool							forceShadowCaps;
	bool							useShadowPreciseInsideTest;
	bool							useShadowDepthBounds;
	// temp
	byte* 							tempCullBits;			// temp buffer in SPU local memory
	// output
	int* 							numShadowIndices;		// streamed out to main memory
	int* 							renderZFail;			// streamed out to main memory
	float* 							shadowZMin;				// streamed out to main memory
	float* 							shadowZMax;				// streamed out to main memory
	volatile shadowVolumeState_t* 	shadowVolumeState;		// streamed out to main memory
	// next in chain on view entity
	staticShadowVolumeParms_t* 		next;
	int								pad[3];
};


void StaticShadowVolumeJob( const staticShadowVolumeParms_t* parms );
void StaticShadowVolume_SetupSPURSHeader( CellSpursJob128* job, const staticShadowVolumeParms_t* parms );

#endif // !__STATICSHADOWVOLUME_H__
