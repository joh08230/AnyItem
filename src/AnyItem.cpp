/*
 * Copyright Regents of the University of Minnesota, 2017.  This software is released under the following license: http://opensource.org/licenses/
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include "AnyItem.h"
#include "impl/BlankItem.h"
#include "impl/DictionaryItemImpl.h"
#include "impl/ArrayItemImpl.h"

namespace any {

AnyItem::AnyItem() : impl(BlankItemImpl::instance()), readOnly(false) {
	state = impl->createItem();
	sanityCheck = getSanityCheckValue();
}

AnyItem::AnyItem(AnyItemImpl* impl) : impl(impl), readOnly(false) {
	state = impl->createItem();
	sanityCheck = getSanityCheckValue();
}

AnyItem::AnyItem(const AnyItem& item) : impl(BlankItemImpl::instance()), readOnly(false) {
	state = impl->createItem();
	copy(item);
	sanityCheck = getSanityCheckValue();
}

AnyItem::~AnyItem() {
	if (sanityCheck == getSanityCheckValue()) {
		impl->deleteItem(state);
	}
}

AnyItem& AnyItem::toArray() {
	if (impl == BlankItemImpl::instance() && readOnly) {
		return *this;
	}

	if (impl != ArrayItemImpl::instance()) {
		impl = ArrayItemImpl::instance();
		impl->deleteItem(state);
		state = impl->createItem();
	}

	return *this;
}

void AnyItem::remove(const std::string& key) {
	impl->remove(key, state);
}

std::vector<std::string> AnyItem::getKeys() const {
	return impl->getKeys(state);
}

AnyItem& AnyItem::operator [](const std::string& key) {
	if (impl == BlankItemImpl::instance() && !readOnly) {
		impl = DictionaryItemImpl::instance();
		impl->deleteItem(state);
		state = impl->createItem();
	}

	return impl->getItem(key, state);
}

const AnyItem& AnyItem::operator [](const std::string& key) const {
	return impl->getItemConst(key, state);
}

void AnyItem::copy(const AnyItem& item) {
	if (impl == BlankItemImpl::instance() && readOnly) {
		return;
	}

	if (sanityCheck == getSanityCheckValue()) {
		impl->deleteItem(state);
	}

	impl = item.impl;
	state = impl->createItem();
	readOnly = item.readOnly;
	impl->copyItem(item.state, state);
}

void* AnyItem::getValue() const {
	return impl->getValue(state);
}

AnyItem& AnyItem::blank() {
	return BlankItem::instance();
}

void AnyItem::pushValue(const AnyItem& item) {
	toArray();
	impl->push(item, state);
}

void AnyItem::remove(int index) {
	impl->remove(index, state);
}

AnyItem& AnyItem::operator[](int index) {
	return impl->getItem(index, state);
}

const AnyItem& AnyItem::operator[](int index) const {
	return impl->getItem(index, state);
}

int AnyItem::size() {
	return impl->size(state);
}

std::ostream& operator<<(std::ostream& stream, const AnyItem& item) {
	item.impl->write(stream, item.state);
	return stream;
}

std::istream& operator>>(std::istream& stream, AnyItem& item) {
	item.impl->read(stream, item.state);
	return stream;
}

bool AnyItem::isBlank() const {
	return impl == BlankItemImpl::instance();
}

void AnyItem::set(const AnyItem& item) {
	this->copy(item);
}

} /* namespace any */

