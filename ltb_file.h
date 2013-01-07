#include <stdint.h>

#define MODEL_MIN_VERSION 23

struct LtbHeader {
  uint8 FileType;
	uint16 FileVersion;
	uint8 iReserved1;
	uint32 iReserved2;
	uint32 iReserved3;
	uint32 iReserved4;
};

struct LtbInfo {
	uint32		m_nKeyFrames;		// Number of keyframes.
	uint32		m_nParentAnims;		// Number of animations (that come from us).
	uint32		m_nNodes;			// Number of nodes.
	uint32		m_nPieces;			// Number of pieces.
	uint32		m_nChildModels;		// Number of child models (including the self child model).
	uint32		m_nTris;			// Number of triangles.
	uint32		m_nVerts;			// Number of vertices.
	uint32		m_nVertexWeights;	// Number of vertex weights.
	uint32		m_nLODs;			// Number of LODs.
	uint32		m_nSockets;			// Number of sockets.
	uint32		m_nWeightSets;		// Number of weight sets.
	uint32		m_nStrings;			// How many strings we're allocating.
	uint32		m_StringLengths;	// Sum of all string lengths (not including null terminator).
	uint32		m_VertAnimDataSize; // byte size of the vertex animation data.
	uint32		m_nAnimData;		// byte size of the animation data
};
