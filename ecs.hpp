#pragma once

#include <cstdint>

#include "Component.hpp"

using cmpId_type = uint8_t;
using grpId_type = uint8_t;

namespace ecs {


	enum comId : cmpId_type
	{
		_Transform = 0,
		_frmImage,
		_brkAsteroid,
		_follow,
		_reappear,
		_bullet,
		_framed,

		_last_cmp_id
	};

	enum grpId : grpId_type
	{
		_grp_Asteroids,
		_grp_Bullets,
		_grp_General,

		_last_grp_id
	};

	constexpr cmpId_type maxCompId = _last_cmp_id;
	constexpr grpId_type maxGroupId = _last_grp_id;

}


