/// DomainGraph.h
/// Shaun Harker
/// 2015-05-24

#ifndef DSGRN_DOMAINGRAPH_H
#define DSGRN_DOMAINGRAPH_H

#include "common.h"
#include "Parameter/Parameter.h"
#include "Graph/Digraph.h"
#include "Dynamics/Annotation.h"
#include "Graph/Components.h"

struct DomainGraph_;

class DomainGraph {
public:
  /// constructor
  DomainGraph ( void );

  /// DomainGraph
  ///   Construct based on parameter and network
  DomainGraph ( Parameter const parameter );

  /// assign
  ///   Construct based on parameter and network
  void
  assign ( Parameter const parameter );

  /// digraph
  ///   Return underlying digraph
  Digraph const
  digraph ( void ) const;  

  /// dimension
  ///   Return dimension of phase space
  uint64_t
  dimension ( void ) const;

  /// label
  ///   Given a domain, return a 64-bit integer 
  ///   which indicates whether each wall is an entrance
  ///   wall or an absorbing wall. The information is
  ///   encoded bitwise for the 2*d walls in the following pattern:
  ///     left-0, left-1, left-2, ..., left-(d-1),
  ///     right-0, right-1, ... right(d-1)
  ///   A bit of 0 means entrance and 1 means absorbing.
  uint64_t 
  label ( uint64_t domain ) const;

  /// direction
  ///   Given adjacent domains, return the variable
  ///   in which they differ. Undefined behavior for 
  ///   non-adjacent domains
  uint64_t
  direction ( uint64_t source, uint64_t target ) const;

  /// annotate
  Annotation const
  annotate ( Component const& vertices ) const;

  /// operator <<
  ///   Emit data to stream in graphviz format
  friend std::ostream& operator << ( std::ostream& stream, DomainGraph const& dg );

private:
  std::shared_ptr<DomainGraph_> data_;
  /// serialize
  ///   For use with BOOST Serialization library,
  ///   which is used by the cluster-delegator MPI package
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version) {
    ar & data_;
  }
};

struct DomainGraph_ {
  uint64_t dimension_;
  Digraph digraph_;
  Parameter parameter_;
  std::vector<uint64_t> labelling_;
  std::unordered_map<uint64_t,uint64_t> direction_;
  /// serialize
  ///   For use with BOOST Serialization library,
  ///   which is used by the cluster-delegator MPI package
  friend class boost::serialization::access;
  template<class Archive>
  void serialize(Archive & ar, const unsigned int version) {
    ar & dimension_;
    ar & digraph_;
    ar & parameter_;
    ar & labelling_;
    ar & direction_;
  }
};

#endif
