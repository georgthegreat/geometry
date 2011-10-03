// Boost.Geometry (aka GGL, Generic Geometry Library)
//
// Boost.Index - R-tree polymorphic nodes
//
// Copyright 2011 Adam Wulkiewicz.
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_NODE_NODE_DEFAULT_HPP
#define BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_NODE_NODE_DEFAULT_HPP

#include <vector>

#include <boost/geometry/algorithms/expand.hpp>

namespace boost { namespace geometry { namespace index {

namespace detail { namespace rtree {

// visitor forward declaration
template <typename Value, typename Parameters, typename Box, typename Tag, bool IsVisitableConst>
struct visitor_poly;

// nodes types

template <typename Value, typename Parameters, typename Box, typename Tag>
struct node_poly
{
    virtual ~node_poly() {}
    virtual void apply_visitor(visitor_poly<Value, Parameters, Box, Tag, false> &) = 0;
    virtual void apply_visitor(visitor_poly<Value, Parameters, Box, Tag, true> &) const = 0;
};

template <typename Value, typename Parameters, typename Box, typename Tag>
struct internal_node_poly : public node_poly<Value, Parameters, Box, Tag>
{
    typedef std::vector<
        std::pair<Box, node_poly<Value, Parameters, Box, Tag> *>
    > elements_type;

    void apply_visitor(visitor_poly<Value, Parameters, Box, Tag, false> & v) { v(*this); }
    void apply_visitor(visitor_poly<Value, Parameters, Box, Tag, true> & v) const { v(*this); }

    elements_type elements;
};

template <typename Value, typename Parameters, typename Box, typename Tag>
struct leaf_poly : public node_poly<Value, Parameters, Box, Tag>
{
    typedef std::vector<Value> elements_type;

    void apply_visitor(visitor_poly<Value, Parameters, Box, Tag, false> & v) { v(*this); }
    void apply_visitor(visitor_poly<Value, Parameters, Box, Tag, true> & v) const { v(*this); }

    elements_type elements;
};

// nodes traits

template <typename Value, typename Parameters, typename Box, typename Tag>
struct node
{
    typedef node_poly<Value, Parameters, Box, Tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Tag>
struct internal_node
{
    typedef internal_node_poly<Value, Parameters, Box, Tag> type;
};

template <typename Value, typename Parameters, typename Box, typename Tag>
struct leaf
{
    typedef leaf_poly<Value, Parameters, Box, Tag> type;
};

// nodes conversion

template <typename Derived, typename Parameters, typename Value, typename Box, typename Tag>
inline Derived & get(node_poly<Value, Parameters, Box, Tag> & n)
{
    assert(dynamic_cast<Derived*>(&n));
    return static_cast<Derived&>(n);
}

template <typename Derived, typename Parameters, typename Value, typename Box, typename Tag>
inline Derived * get(node_poly<Value, Parameters, Box, Tag> * n)
{
    assert(dynamic_cast<Derived*>(n));
    return static_cast<Derived*>(n);
}

// visitor

template <typename Value, typename Parameters, typename Box, typename Tag>
struct visitor_poly<Value, Parameters, Box, Tag, true>
{
    typedef typename internal_node<Value, Parameters, Box, Tag>::type internal_node;
    typedef typename leaf<Value, Parameters, Box, Tag>::type leaf;

    virtual ~visitor_poly() {}

    virtual void operator()(internal_node const&) = 0;
    virtual void operator()(leaf const&) = 0;
};

template <typename Value, typename Parameters, typename Box, typename Tag>
struct visitor_poly<Value, Parameters, Box, Tag, false>
{
    typedef typename internal_node<Value, Parameters, Box, Tag>::type internal_node;
    typedef typename leaf<Value, Parameters, Box, Tag>::type leaf;

    virtual ~visitor_poly() {}

    virtual void operator()(internal_node &) = 0;
    virtual void operator()(leaf &) = 0;
};

// visitor traits

template <typename Value, typename Parameters, typename Box, typename Tag, bool IsVisitableConst>
struct visitor
{
    typedef visitor_poly<Value, Parameters, Box, Tag, IsVisitableConst> type;
};

template <typename Visitor, typename Visitable>
inline void apply_visitor(Visitor &v, Visitable & n)
{
    n.apply_visitor(v);
}

// element's indexable type

template <typename Value, typename Translator>
struct element_indexable_type
{
	typedef typename Translator::indexable_type type;
};

template <typename Value, typename Parameters, typename Box, typename Tag, typename Translator>
struct element_indexable_type<
    std::pair<Box, node_poly<Value, Parameters, Box, Tag> *>,
    Translator
>
{
    typedef Box type;
};

// element's indexable getter

template <typename Value, typename Translator>
inline typename Translator::indexable_type const&
element_indexable(Value const& el, Translator const& tr)
{
	return tr(el);
}

template <typename Value, typename Parameters, typename Box, typename Tag, typename Translator>
inline Box const&
element_indexable(
    std::pair< Box, node_poly<Value, Parameters, Box, Tag> *> const& el,
    Translator const&)
{
    return el.first;
}

// nodes elements

template <typename Node>
struct elements_type
{
	typedef typename Node::elements_type type;
};

template <typename Node>
inline typename elements_type<Node>::type &
elements(Node & n)
{
	return n.elements;
}

template <typename Node>
inline typename elements_type<Node>::type const&
elements(Node const& n)
{
	return n.elements;
}

// elements box

template <typename Box, typename FwdIter, typename Translator>
inline Box elements_box(FwdIter first, FwdIter last, Translator const& tr)
{
    BOOST_GEOMETRY_INDEX_ASSERT(first != last, "Can't calculate element's box");

	Box result;

	geometry::convert(element_indexable(*first, tr), result);
	++first;

	for ( ; first != last ; ++first )
		geometry::expand(result, element_indexable(*first, tr));

	return result;
}

// allocators

template <typename Value, typename Parameters, typename Box, typename Tag, typename Allocator>
struct allocators_poly
{
    typedef Allocator allocator_type;
    typedef typename allocator_type::size_type size_type;

    typedef typename allocator_type::template rebind<
        typename internal_node<Value, Parameters, Box, Tag>::type
    >::other internal_node_allocator_type;

    typedef typename allocator_type::template rebind<
        typename leaf<Value, Parameters, Box, Tag>::type
    >::other leaf_allocator_type;

    inline explicit allocators_poly(Allocator alloc)
        : allocator(alloc)
        , internal_node_allocator(allocator)
        , leaf_allocator(allocator)
    {}

    allocator_type allocator;
    internal_node_allocator_type internal_node_allocator;
    leaf_allocator_type leaf_allocator;
};

// allocators

template <typename Value, typename Parameters, typename Box, typename Tag, typename Allocator>
struct allocators
{
    typedef allocators_poly<Value, Parameters, Box, Tag, Allocator> type;
};

// create_node_poly

template <typename Allocator, typename Node>
struct create_node_poly
{
    template <typename RetNode>
    static inline RetNode * apply(Allocator & allocator)
    {
        Node * p = allocator.allocate(1);

        if ( 0 == p )
            throw std::bad_alloc();

        try
        {
            allocator.construct(p, Node());
        }
        catch(...)
        {
            allocator.deallocate(p, 1);
            throw;
        }

        return p;
    }
};

// destroy_node_poly

template <typename Allocator, typename Node>
struct destroy_node_poly
{
    template <typename BaseNode>
    static inline void apply(Allocator & allocator, BaseNode * n)
    {
        Node * p = rtree::get<Node>(n);
        allocator.destroy(p);
        allocator.deallocate(p, 1);
    }
};

// create_node

template <typename Allocators, typename Node>
struct create_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_NODE_TYPE,
        (create_node));
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    internal_node_poly<Value, Parameters, Box, Tag>
>
{
    static inline typename node<Value, Parameters, Box, Tag>::type * apply(Allocators & allocators)
    {
        return create_node_poly<
            typename Allocators::internal_node_allocator_type,
            internal_node_poly<Value, Parameters, Box, Tag>
        >::template apply<
            typename node<Value, Parameters, Box, Tag>::type
        >(allocators.internal_node_allocator);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct create_node<
    Allocators,
    leaf_poly<Value, Parameters, Box, Tag>
>
{
    static inline typename node<Value, Parameters, Box, Tag>::type * apply(Allocators & allocators)
    {
        return create_node_poly<
            typename Allocators::leaf_allocator_type,
            leaf_poly<Value, Parameters, Box, Tag>
        >::template apply<
            typename node<Value, Parameters, Box, Tag>::type
        >(allocators.leaf_allocator);
    }
};

// destroy_node

template <typename Allocators, typename Node>
struct destroy_node
{
    BOOST_MPL_ASSERT_MSG(
        (false),
        NOT_IMPLEMENTED_FOR_THIS_NODE_TYPE,
        (destroy_node));
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    internal_node_poly<Value, Parameters, Box, Tag>
>
{
    static inline void apply(Allocators & allocators, typename node<Value, Parameters, Box, Tag>::type * n)
    {
        destroy_node_poly<
            typename Allocators::internal_node_allocator_type,
            internal_node_poly<Value, Parameters, Box, Tag>
        >::apply(allocators.internal_node_allocator, n);
    }
};

template <typename Allocators, typename Value, typename Parameters, typename Box, typename Tag>
struct destroy_node<
    Allocators,
    leaf_poly<Value, Parameters, Box, Tag>
>
{
    static inline void apply(Allocators & allocators, typename node<Value, Parameters, Box, Tag>::type * n)
    {
        destroy_node_poly<
            typename Allocators::leaf_allocator_type,
            leaf_poly<Value, Parameters, Box, Tag>
        >::apply(allocators.leaf_allocator, n);
    }
};

}} // namespace detail::rtree

}}} // namespace boost::geometry::index

#endif // BOOST_GEOMETRY_EXTENSIONS_INDEX_RTREE_NODE_NODE_DEFAULT_HPP
