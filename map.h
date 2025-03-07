/***********************************************************************
 * Header:
 *    MAP
 * Summary:
 *    Our custom implementation of a std::map
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        map                 : A class that represents a map
 *        map::iterator       : An iterator through a map
 * Author
 *    Nathan Bird, Brock Hoskins
 ************************************************************************/

#pragma once

#include "pair.h"            // for custom::pair
#include <utility>           // for std::pair
#include "bst.h"             // for custom::bst
#include <initializer_list>  // for std::initializer_list
#include <stdexcept>         // for std::out_of_range

#ifndef debug
#ifdef DEBUG
#define debug(x) x
#else
#define debug(x)
#endif // DEBUG
#endif // !debug

class TestMap;

namespace custom
{

/*****************************************************************
 * MAP
 * Create a Map, similar to a Binary Search Tree
 *****************************************************************/
   template <class K, class V>
   class map
   {
      friend class ::TestMap;

      template <class KK, class VV>
      friend void swap(map<KK, VV>& lhs, map<KK, VV>& rhs);
   public:
      using Pair = custom::pair<K, V>;
      using BST = BST<Pair>;

      // 
      // Construct
      //
      map()
      {}
      map(const map& rhs) : bst(rhs.bst)
      {}
      map(map&& rhs) : bst(std::move(rhs.bst))
      {}
      template <class Iterator>
      map(Iterator first, Iterator last)
      {
         insert(first, last);
      }
      map(const std::initializer_list<Pair>& il)
      {
         *this = il;
      }
      ~map() // calls bst::destructor which clears itself
      {}

      //
      // Assign
      //
      map& operator =(const map& rhs)
      {
         bst = rhs.bst;
         return *this;
      }
      map& operator =(map&& rhs)
      {
         clear();
         bst = std::move(rhs.bst);
         return *this;
      }
      map& operator =(const std::initializer_list<Pair>& il)
      {
         clear();
         insert(il);
         return *this;
      }

      // 
      // Iterator
      //
      class iterator;
      iterator begin()
      {
         // Explicitly convert bst::iterator to map::iterator
         return map::iterator(bst.begin());
      }
      iterator end()
      {
         // Explicitly convert bst::iterator to map::iterator
         return map::iterator(bst.end());
      }

      // 
      // Access
      //
      const V& operator [] (const K& k) const;
      V& operator [] (const K& k);
      const V& at (const K& k) const;
      V& at (const K& k);
      iterator find(const K& k)
      {
         // custom::pair has a constructor that just takes first/key
         pair<K, V> searchPair(k);
         return map::iterator(bst.find(searchPair));
      }

      //
      // Insert
      //
      custom::pair<typename map::iterator, bool> insert(Pair&& rhs)
      {
         std::pair<typename BST::iterator, bool> itBSTPair = bst.insert(std::move(rhs), /*keepUnique: */true);
         return custom::make_pair(map::iterator(itBSTPair.first), itBSTPair.second);
      }
      custom::pair<typename map::iterator, bool> insert(const Pair& rhs)
      {
         std::pair<typename BST::iterator, bool> itBSTPair = bst.insert(rhs, /*keepUnique: */true);
         return custom::make_pair(map::iterator(itBSTPair.first), itBSTPair.second);
      }

      template <class Iterator>
      void insert(Iterator first, Iterator last)
      {
         while (first != last)
         {
            insert(*first);
            ++first;
         }
      }
      void insert(const std::initializer_list<Pair>& il)
      {
         for (const Pair& pair : il)
            insert(pair);
      }

      //
      // Remove
      //
      void clear() noexcept
      {
         bst.clear();
      }
      size_t   erase(const K& k);
      iterator erase(iterator it);
      iterator erase(iterator first, iterator last);

      //
      // Status
      //
      bool empty() const noexcept
      {
         return size() == 0;
      }
      size_t size() const noexcept
      {
         return bst.size();
      }


   private:

      // the students DO NOT need to use a nested class
      BST bst;
   };


   /**********************************************************
    * MAP ITERATOR
    * Forward and reverse iterator through a Map, just call
    * through to BSTIterator
    *********************************************************/
   template <typename K, typename V>
   class map<K, V>::iterator
   {
      friend class ::TestMap;
      template <class KK, class VV>
      friend class custom::map;
   public:
      //
      // Construct
      //
      iterator()
      {}
      iterator(const typename BST::iterator& rhs) : it(rhs)
      {}
      iterator(const iterator& rhs) : it(rhs.it)
      {}

      //
      // Assign
      //
      iterator& operator =(const iterator& rhs)
      {
         it = rhs.it;
         return *this;
      }

      //
      // Compare
      //
      bool operator ==(const iterator& rhs) const
      {
         return it == rhs.it;
      }
      bool operator !=(const iterator& rhs) const
      {
         return it != rhs.it;
      }

      // 
      // Access
      //
      const pair<K, V>& operator *() const
      {
         return *it;
      }

      //
      // Increment
      //
      iterator& operator ++()
      {
         ++it;
         return *this;
      }
      iterator operator ++(int postfix)
      {
         iterator temp(*this);
         ++it;
         return temp;
      }
      iterator& operator --()
      {
         --it;
         return *this;
      }
      iterator operator --(int postfix)
      {
         iterator temp(*this);
         --it;
         return *this;
      }

   private:

      // Member variable
      typename BST::iterator it;
   };


   /*****************************************************
    * MAP :: SUBSCRIPT
    * Retrieve an element from the map
    ****************************************************/
   template <typename K, typename V>
   V& map<K, V>::operator [](const K& key)
   {
      Pair pair(key);
      std::pair<typename BST::iterator, bool> returnValue = bst.insert(pair, /*keepUnique: */true);
      typename BST::iterator itBST = returnValue.first;
      return itBST.pNode->data.second;
   }

   /*****************************************************
    * MAP :: SUBSCRIPT
    * Retrieve an element from the map
    ****************************************************/
   template <typename K, typename V>
   const V& map<K, V>::operator [](const K& key) const
   {
      Pair pair(key);
      typename BST::iterator itBST = bst.find(pair);
      if (itBST != bst.end())
         return itBST.pNode->data.second;
      else
         return pair.second;
   }

   /*****************************************************
    * MAP :: AT
    * Retrieve an element from the map
    ****************************************************/
   template <typename K, typename V>
   V& map<K, V>::at(const K& key)
   {
      iterator at(find(key));
      if (at != end())
         // can't use `*at` because there is only a const version, need non-const
         return at.it.pNode->data.second;
      throw std::out_of_range("invalid map<K, T> key");
   }

   /*****************************************************
    * MAP :: AT READ ONLY
    * Retrieve an element from the map
    ****************************************************/
   template <typename K, typename V>
   const V& map<K, V>::at(const K& key) const
   {
      iterator at(find(key));
      if (at != end())
         // `map::iterator::operator *()` returns `const pair&`, therefore `pair.second` will be `const V&`
         return at->second; // same as `(*at).second`
      throw std::out_of_range("invalid map<K, T> key");
   }

   /*****************************************************
    * SWAP
    * Swap two maps
    ****************************************************/
   template <typename K, typename V>
   void swap(map<K, V>& lhs, map<K, V>& rhs)
   {
      std::swap(lhs.bst, rhs.bst);
   }

   /*****************************************************
    * ERASE
    * Erase one element
    ****************************************************/
   template <typename K, typename V>
   size_t map<K, V>::erase(const K& k)
   {
      iterator it(find(k));
      if (it != end())
      {
         erase(it);
         return 1;
      }
      return 0;
   }

   /*****************************************************
    * ERASE
    * Erase several elements
    ****************************************************/
   template <typename K, typename V>
   typename map<K, V>::iterator map<K, V>::erase(map<K, V>::iterator first, map<K, V>::iterator last)
   {
      while (first != last)
         first = erase(first);
      return first;
   }

   /*****************************************************
    * ERASE
    * Erase one element
    ****************************************************/
   template <typename K, typename V>
   typename map<K, V>::iterator map<K, V>::erase(map<K, V>::iterator it)
   {
      return map::iterator(bst.erase(it.it));
   }

}; //  namespace custom

