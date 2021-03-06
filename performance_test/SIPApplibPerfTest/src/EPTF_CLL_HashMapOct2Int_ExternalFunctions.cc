/******************************************************************************
 * Copyright (c) 2000-2020 Ericsson Telecom AB
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v2.0
 * which accompanies this distribution, and is available at
 * https://www.eclipse.org/org/documents/epl-2.0/EPL-2.0.html
 ******************************************************************************/
//  File:     EPTF_CLL_HashMapOct2Int_ExternalFunctions.cc
//  Rev:      <RnXnn>
//  Prodnr:   CNL 113 512
//  Updated:  2011-11-17
//  Contact:  http://ttcn.ericsson.se
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//  File: EPTF_CLL_HashMapOct2Int_ExternalFunctions.cc
//
//  Purpose:
//    Provide implementation of external c++ functions of oct2int HashMaps.
//
///////////////////////////////////////////////////////////////

//#include "EPTF_CLL_HashMap_Functions.hh"
#include "EPTF_CLL_HashMap_ExternalFunctions.hh"

#ifdef EPTF_DEBUG
#define HASHMAP_OCT2INT_DEBUG_MEMLEAK // enable memleak debug
#endif

#ifdef HASHMAP_OCT2INT_DEBUG_MEMLEAK
#include "EPTF_CLL_Common_Definitions.hh"
#endif


//EPTF__CLL__HashMap__Functions
namespace EPTF__CLL__HashMapOct2Int__Functions {
using namespace EPTF__CLL__HashMap__Functions;


struct EPTF_HashMap_hash
{
size_t
      operator()(const OCTETSTRING& cs) const
  {
    unsigned long __h = 0;
    const unsigned char* __s=cs;
    const unsigned char* end = __s + cs.lengthof();
    for ( ; __s<end; ++__s)
      __h = 5 * __h + *__s;
    return size_t(__h);
  }
};

///////////////////////////////////////////////////////////
// Type: Oct2IntHashMapType
//
// Purpose:
//   Type of hashmap. octetstring -> int
//
// Elements:
//   key - key of hashmap
//   data - data of hashmap
//   hashfcn - hashfunction of hashmap, built in, can be changed
//   equalkey -  equality function of hashmap, EPTF__oct2int__HashMap__Eqint
//
///////////////////////////////////////////////////////////

typedef HashMapTypeCT<OCTETSTRING, EPTF_HashMap_hash, EPTF_HashMap_EqDef<OCTETSTRING> > Oct2IntHashMapType;

///////////////////////////////////////////////////////////
// Type: Oct2IntHashMapTypePtr
//
// Purpose:
//   Pointer to hashmap.
//
///////////////////////////////////////////////////////////

typedef Oct2IntHashMapType* Oct2IntHashMapTypePtr;

///////////////////////////////////////////////////////////
// Variable: v_Oct2IntHashMap
//
// Purpose:
//   Octetstring->Integer type HashMap variable
//
///////////////////////////////////////////////////////////

Oct2IntHashMapTypePtr v_Oct2IntHashMap = NULL;

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Cleanup
//
// Purpose:
//   External function for deleting ALL hashmaps.
//
// Parameters:
//   -
// Return Value:
//   -
//
//  Errors:
//   -
///////////////////////////////////////////////////////////

void f_EPTF_oct2int_HashMap_Cleanup()
{
  delete v_Oct2IntHashMap;
  v_Oct2IntHashMap = NULL;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Init
//
// Purpose:
//   Initializes the hashmap.
//   This function is DEPRECATED! Will be removed after this release!
//
// Parameters:
//   -
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f_EPTF_oct2int_HashMap_Init()
{
  if (NULL != v_Oct2IntHashMap) {
    f_EPTF_oct2int_HashMap_Cleanup();
  }
  v_Oct2IntHashMap = new Oct2IntHashMapType;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_New
//
// Purpose:
//   Creates a new hashmap.
//
// Parameters:
//   pl_name - *in* *charstring* - the name of the hashmap
//
// Return Value:
//   integer - the ID of the hashmap
///////////////////////////////////////////////////////////

INTEGER f__EPTF__oct2int__HashMap__New (
  const CHARSTRING& pl_name)
{
  if ( v_Oct2IntHashMap )
  {
    return v_Oct2IntHashMap->newHashmap(pl_name);
  }
  return -1;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_GetID
//
// Purpose:
//   To get the ID of the hashmap from the name.
//
// Parameters:
//   pl_name - *in* *charstring* - the name of the hashmap
//   pl_id - *inout* *integer* - the ID of the hashmap
//
// Return Value:
//   boolean - true if ID found
///////////////////////////////////////////////////////////

BOOLEAN f__EPTF__oct2int__HashMap__GetID (
  const CHARSTRING& pl_name,
  INTEGER& pl_id)
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->getID(pl_name, pl_id);
	  }
return false;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Delete
//
// Purpose:
//   Deletes the hashmap.
//
// Parameters:
//   pl_name - *in* *charstring* - the name of the hashmap
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Delete (
  const CHARSTRING& pl_name)
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->deleteHashMap(pl_name);
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_DeleteById
//
// Purpose:
//   Deletes the hashmap.
//
// Parameters:
//   pl_id - *in* *integer* - the id of the hashmap
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__DeleteById (
  const INTEGER& pl_id)
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->deleteHashMap(pl_id);
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_DumpByID
//
// Purpose:
//   Dump the content of a specific hashmap by ID.
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__DumpByID (
  const INTEGER& pl_id)
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->dumpByID(pl_id);
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Dump
//
// Purpose:
//   Dump the content of a specific hashmap by name.
//
// Parameters:
//   pl_name - *in* *charstring* - the name of the hashmap
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Dump (
  const CHARSTRING& pl_name)
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->dump(pl_name);
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_DumpAll
//
// Purpose:
//   Dump the content of all hashmaps.
//
// Parameters:
//   -
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__DumpAll ()
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->dumpAll();
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Assign
//
// Purpose:
//   Assignment of one hashmap to another. pl_id1 := pl_id2.
//
// Parameters:
//   pl_id1 - *in* *integer* - the ID of the hashmap1
//   pl_id2 - *in* *integer* - the ID of the hashmap2
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Assign (
  const INTEGER& pl_id1,
  const INTEGER& pl_id2)
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->assign(pl_id1, pl_id2);
	  }
}



///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Insert
//
// Purpose:
//   Inserts an element to hashmap.
//   In C++ STL:
//               std::pair<iterator, bool>
//               insert(const value_type& x)
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_key - *in* *octetstring* - the key of the hashmap
//   pl_data - *in* *integer* - the data to be inserted
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Insert (
  const INTEGER& pl_id,
  const OCTETSTRING& pl_key,
  const INTEGER& pl_data )
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->insert<OCTETSTRING>(pl_id, pl_key, pl_data);
	  }
};

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Update
//
// Purpose:
//   Updates an element in hashmap.
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_key - *in* *octetstring* - the key of the hashmap
//   pl_data - *in* *integer* - the data to be inserted
//
// Return Value:
//   -
///////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Update (
  const INTEGER& pl_id,
  const OCTETSTRING& pl_key,
  const INTEGER& pl_data )
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->update<OCTETSTRING>(pl_id, pl_key, pl_data);
	  }
};

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Find
//
// Purpose:
//   Finds an element in hashmap.
//   In C++ STL:
//               iterator find(const key_type& k)
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_key - *in* *octetstring* - the key of the hashmap
//   pl_data - *out* *integer* - the searched data
//
// Return Value:
//   boolean - if we found the data
///////////////////////////////////////////////////////////

BOOLEAN f__EPTF__oct2int__HashMap__Find (
  const INTEGER& pl_id,
  const OCTETSTRING& pl_key,
  INTEGER& pl_data )
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->find<OCTETSTRING>(pl_id, pl_key, pl_data);
	  }
	  return false;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Erase
//
// Purpose:
//   Erases an element from hashmap.
//   In C++ STL:
//               size_type erase(const key_type& k)
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_key - *in* *octetstring* - the key of the hashmap
//
// Return Value:
//   -
/////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Erase (
  const INTEGER& pl_id,
  const OCTETSTRING& pl_key )
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->erase<OCTETSTRING>(pl_id,pl_key);
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Clear
//
// Purpose:
//   Clear all elements from hashmap.
//   In C++ STL:
//               void clear()
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//
// Return Value:
//   -
/////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Clear (
  const INTEGER& pl_id )
{
	  if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->clear(pl_id);
	  }
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Size
//
// Purpose:
//   Returns the size of hashmap. Size = the used buckets.
//   In C++ STL:
//               size_type size() const
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//
// Return Value:
//   integer - the size of hashmap
//////////////////////////////////////////////////////////

INTEGER f__EPTF__oct2int__HashMap__Size (
 const INTEGER& pl_id )
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->size(pl_id);
	  }
	  return 0;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_MaxSize
//
// Purpose:
//   Returns the maximum size of hashmap.
//   In C++ STL:
//               size_type max_size() const
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//
// Return Value:
//   float - the maximum size of hashmap
//////////////////////////////////////////////////////////

FLOAT f__EPTF__oct2int__HashMap__MaxSize (
 const INTEGER& pl_id )
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->maxSize(pl_id);
	  }
	  return -1;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_CallHashFunc
//
// Purpose:
//   Calls the hash function of a given hashmap.
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap, which hashfunction we use
//   pl_key - *in* *octetstring* - the key of the hashmap
//
// Return Value:
//   integer - the hashvalue of key
//////////////////////////////////////////////////////////
INTEGER f__EPTF__oct2int__HashMap__CallHashFunc(
  const INTEGER& pl_id,
  const OCTETSTRING& pl_key)
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->callHashFunc<OCTETSTRING>(pl_id, pl_key);
	  }
	  return -1;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Empty
//
// Purpose:
//   Check whether the hashmap is empty. true if the unordered_map's size is 0.
//   In C++ STL:
//               bool empty() cons
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//
// Return Value:
//   boolean - true if the unordered_map's size is 0.
//////////////////////////////////////////////////////////

BOOLEAN f__EPTF__oct2int__HashMap__Empty (
  const INTEGER& pl_id )
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->empty(pl_id);
	  }
	  return false;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Resize
//
// Purpose:
//   Increases the bucket count to at least pl_hashsize.
//   In C++ STL:
//               void resize(size_type n)
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_hashsize - *in* *integer* - the new bucketsize
//
// Return Value:
//   -
//////////////////////////////////////////////////////////

void f__EPTF__oct2int__HashMap__Resize (
  const INTEGER& pl_id,
  const INTEGER& pl_hashsize)
{
	  /*if ( v_Oct2IntHashMap )
	  {
	    v_Oct2IntHashMap->resize(pl_id,pl_hashsize);
	  }*/
};

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_BucketCount
//
// Purpose:
//   Returns the number of buckets used by the unordered_map. This is the booked size.
//   It contains empty buckets also.
//   In C++ STL:
//               size_type bucket_count() const
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//
// Return Value:
//   integer - the bucketsize
//////////////////////////////////////////////////////////

INTEGER f__EPTF__oct2int__HashMap__BucketCount (
  const INTEGER& pl_id )
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->bucketCount(pl_id);
	  }
	  return -1;
};

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Begin
//
// Purpose:
//   External function call to get the first element of hashmap.
//   In TTCN we can't use iterators, so we get back the first key element.
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_key - *inout* *octetstring* - the first key in hashmap
//
// Return Value:
//   boolean - false if the hashmap is empty
//////////////////////////////////////////////////////////

BOOLEAN f__EPTF__oct2int__HashMap__Begin(
  const INTEGER& pl_id,
  OCTETSTRING& pl_key)
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->begin<OCTETSTRING>(pl_id, pl_key);
	  }
	  return false;
}

///////////////////////////////////////////////////////////
// Function: f_EPTF_oct2int_HashMap_Next
//
// Purpose:
//   External function call to get the next element of hashmap.
//   In TTCN we can't use iterators, so we get back a key element's next key element.
//
// Parameters:
//   pl_id - *in* *integer* - the ID of the hashmap
//   pl_iter - *inout* *octetstring* - in = the iterator of the hashmap (iterator = key)
//                                    out = the next key in hashmap
//
// Return Value:
//   boolean - false if no next key in hashmap
//////////////////////////////////////////////////////////

BOOLEAN f__EPTF__oct2int__HashMap__Next(
  const INTEGER& pl_id,
  OCTETSTRING& pl_iter)
{
	  if ( v_Oct2IntHashMap )
	  {
	    return v_Oct2IntHashMap->next<OCTETSTRING>(pl_id, pl_iter);
	  }
	  return false;
}

}
