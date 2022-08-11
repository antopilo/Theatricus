#pragma once
#include "Node.h"

#include <vector>

namespace Core
{
	class Slate
	{
	private:
		std::vector<Node> _nodes;

	public:
		Slate() = default;
		~Slate() = default;

		void AddNode(const Node& node)
		{
			_nodes.push_back(std::move(node));
		}

		std::vector<Node>& GetNodes()
		{
			return _nodes;
		}
	};
}