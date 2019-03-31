


struct DFA_ArrayBased
{
	struct Node
	{
		std::vector<int> connectedNodes;
		int value;
	}
	
	
	std::vector<Node>  nodes;
	
	
	static DFA_ArrayBased Construct(std::string name)
	{
		// Make nodes
		DFA_ArrayBased finder;
		finder.nodes.resize(name.size());
		
		// Assign Node values
		for(int i = 0; i < name.size(); ++i)
		{
			node.value = name[i];
		}
		
		// Find patterns, connect nodes
		// @TODO
		for(int i = 2; i < finder.nodes.size() - 1; ++i)
		{
		}
		
		return finder;
	}
	
	
	
	
	
	
}