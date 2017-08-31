/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#ifndef DICTIONARYITEMIMPL_H_
#define DICTIONARYITEMIMPL_H_

#include "AnyItemImpl.h"
#include <map>

namespace any {

class DictionaryItemImpl : public AnyItemImpl {
public:
	void* createItem() const;
	void copyItem(void* state, void* newState) const;
	void deleteItem(void* state) const;
	AnyItem& getItem(const std::string& key, void* state) const;
	std::vector<std::string> getKeys(const void* state) const;
	void* getValue(void* state) const;
	void write(std::ostream& out, const void* state) const;
	void read(std::istream& in, void* state) const;
	void remove(const std::string& key, void* state) const;
	const std::type_info& getType() const;
	static AnyItemImpl* instance();
};

} /* namespace any */

#endif /* DICTIONARYITEMIMPL_H_ */