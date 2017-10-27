//=======================================================================
// Copyright 2001 Jeremy G. Siek, Andrew Lumsdaine, Lie-Quan Lee,
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================
#include "stdafx.h"
#include <boost/config.hpp>
#include <iostream>
#include <fstream>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>

using namespace boost;

void demo1()
{
    typedef adjacency_list < listS, vecS, directedS,
    no_property, property < edge_weight_t, int > > graph_t;
  typedef graph_traits < graph_t >::vertex_descriptor vertex_descriptor;
  typedef std::pair<int, int> Edge;

  const int num_nodes = 5;
  enum nodes { A, B, C, D, E };
  char name[] = "ABCDE";
  Edge edge_array[] = { Edge(A, C), Edge(B, B), Edge(B, D), Edge(B, E),
    Edge(C, B), Edge(C, D), Edge(D, E), Edge(E, A), Edge(E, B)
  };
  int weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };
  int num_arcs = sizeof(edge_array) / sizeof(Edge);
  graph_t g(edge_array, edge_array + num_arcs, weights, num_nodes);
  property_map<graph_t, edge_weight_t>::type weightmap = get(edge_weight, g);
  std::vector<vertex_descriptor> p(num_vertices(g));
  std::vector<int> d(num_vertices(g));
  vertex_descriptor s = vertex(A, g);

  dijkstra_shortest_paths(g, s,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

  std::cout << "distances and parents:" << std::endl;
  graph_traits < graph_t >::vertex_iterator vi, vend;
  for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi) {
    std::cout << "distance(" << name[*vi] << ") = " << d[*vi] << ", ";
    std::cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << std::
      endl;
  }
  std::cout << std::endl;

  std::ofstream dot_file("dijkstra-eg.dot");

  dot_file << "digraph D {\n"
    << "  rankdir=LR\n"
    << "  size=\"4,3\"\n"
    << "  ratio=\"fill\"\n"
    << "  edge[style=\"bold\"]\n" << "  node[shape=\"circle\"]\n";

  graph_traits < graph_t >::edge_iterator ei, ei_end;
  for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
    graph_traits < graph_t >::edge_descriptor e = *ei;
    graph_traits < graph_t >::vertex_descriptor
      u = source(e, g), v = target(e, g);
    dot_file << name[u] << " -> " << name[v]
      << "[label=\"" << get(weightmap, e) << "\"";
    if (p[v] == u)
      dot_file << ", color=\"black\"";
    else
      dot_file << ", color=\"grey\"";
    dot_file << "]";
  }
  dot_file << "}";
}

void demo2()
{
    enum nodes {A, B, C, NODE_MAX};
    const char *name = "ABC";
    std::pair<int, int> edge_arr[] = {std::pair<int, int>(A, B), std::pair<int, int>(A, C), std::pair<int, int>(B, C)};
    const int weights[] = {1, 2, 4};

    boost::adjacency_list<vecS, vecS, undirectedS, no_property, property < edge_weight_t, int > >
        adj_list(edge_arr, edge_arr + sizeof(edge_arr) / sizeof(edge_arr[0]), weights, NODE_MAX);

    boost::graph_traits< boost::adjacency_list<vecS, vecS, undirectedS, no_property, property < edge_weight_t, int > > >::vertex_descriptor
        s = boost::vertex(B, adj_list);

    std::vector<boost::graph_traits< boost::adjacency_list<vecS, vecS, undirectedS, no_property, property < edge_weight_t, int > > >::vertex_descriptor> p(boost::num_vertices(adj_list));
    std::vector<int> d(boost::num_vertices(adj_list));

    dijkstra_shortest_paths(adj_list, s,
                          predecessor_map(boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, adj_list))).
                          distance_map(boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, adj_list))));

    std::cout << "distances and parents:" << std::endl;
    boost::graph_traits < boost::adjacency_list<vecS, vecS, undirectedS, no_property, property < edge_weight_t, int > > >::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(adj_list); vi != vend; ++vi)
    {
        std::cout << *vi << " distance(" << name[*vi] << ") = " << d[*vi] << ", ";
        std::cout << "parent(" << name[*vi] << ") = " << name[p[*vi]] << std::endl;
    }

    std::cout << std::endl;
}

int main(int, char *[])
{
    demo2();

    return EXIT_SUCCESS;
}
