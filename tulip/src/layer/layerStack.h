#pragma once

#include <core\core.h>
#include <layer\layer.h>

#include <vector>

namespace tulip {

	class LayerStack {
	public:
		LayerStack();
		~LayerStack();

		void pushLayer(Ref<Layer> layer);
		void pushOverlay(Ref<Layer> overlay);
		void popLayer(Ref<Layer> layer);
		void popOverlay(Ref<Layer> overlay);

		std::vector<Ref<Layer>>::reverse_iterator begin() { return this->m_layers.rbegin(); }
		std::vector<Ref<Layer>>::reverse_iterator end() { return this->m_layers.rend(); }

	private:
		std::vector<Ref<Layer>> m_layers;
		uint32_t m_insertIndex;

	};
}