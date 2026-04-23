#pragma once
#include<math.h>
#include"../../Utility/Vector3.h"
namespace {
	Vector3 RadToPos(float radian, float distance, const Vector3& basePos = { 0.0f,0.0f,0.0f }) {
		Vector3 res = { 0.0f,0.0f,0.0f };
		res.x = cosf(radian);
		res.y = sinf(radian);
		res = res.GetNormalize();
		res *= distance;
		res += basePos;
		return res;
	}
}