#pragma once

// This header is used just to store a couple helpful enums that are used by multiple classes

namespace AXES_PLANES {
	enum PLANE {
		PLANE_XY,
		PLANE_XZ,
		PLANE_YZ,
		PLANE_XW,
		PLANE_YW,
		PLANE_ZW,
		PLANE_SIZE	// not a real plane, just to keep track of how many
	};
	enum AXIS {
		AXIS_X,
		AXIS_Y,
		AXIS_Z,
		AXIS_W,
		AXIS_SIZE	// not a real axis, just used for keeping track of how many
	};
}