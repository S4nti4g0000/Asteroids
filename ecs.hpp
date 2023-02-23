#pragma once

#include <cstdint>

using cmpId_type = uint8_t;

enum comId : cmpId_type
{
	_Transform = 0,
	_frmImage,
	_brkAsteroid,
	_follow,
	_reappear,

	_last_cmp_id
};

constexpr cmpId_type maxCompId = _last_cmp_id;