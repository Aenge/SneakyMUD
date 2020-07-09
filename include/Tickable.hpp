#pragma once

namespace sneaky {
	class Tickable {
	public:
		virtual void onInit();
		virtual void onTick();
		virtual void onDestroy();
	};
}