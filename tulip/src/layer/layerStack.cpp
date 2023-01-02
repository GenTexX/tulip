#include "tulippch.h"
#include "layerStack.h"

namespace tulip {

	LayerStack::LayerStack() {
		this->m_insertIndex = 0;
	}

	LayerStack::~LayerStack() {

	}

	void LayerStack::pushLayer(Ref<Layer> layer) {
		this->m_layers.emplace(this->m_layers.begin() + this->m_insertIndex, layer);
		this->m_insertIndex++;
		layer->onAttach();
	}

	void LayerStack::pushOverlay(Ref<Layer> overlay) {
		this->m_layers.emplace_back(overlay);
		overlay->onAttach();
	}

	void LayerStack::popLayer(Ref<Layer> layer) {

		auto it = std::find(this->m_layers.begin(), this->m_layers.begin() + this->m_insertIndex, layer);

		if (it != this->m_layers.begin() + this->m_insertIndex) {
			(*it)->onDetach();
			this->m_layers.erase(it);
			this->m_insertIndex--;
		}

	}

	void LayerStack::popOverlay(Ref<Layer> overlay) {
		auto it = std::find(this->m_layers.begin() + this->m_insertIndex, this->m_layers.end(), overlay);

		if (it != this->m_layers.end()) {
			(*it)->onDetach();
			this->m_layers.erase(it);
		}
	}

}