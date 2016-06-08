#pragma once
#include "libgp_global.h"
#include <nanoflann.hpp>

namespace LibGP {

	/** An L2-metric KD-tree adaptor for working with data directly
	*  stored in an Eigen Matrix, without duplicating the data storage.
	*  Each colomn in the matrix represents a point in the state space.
	*
	*  Example of usage:
	*	LibGP::KDTreeAdaptor<Eigen::MatrixXd> kdtree(V); 
	*	kdtree.closest(...);
	*
	*  This code is adapted from the KDTreeEigenMatrixAdaptor class of nanoflann.hpp
	*/
	
	template <class MatrixType = MatrixXf, int DIM = 3, class Distance = nanoflann::metric_L2_Simple>
	class KDTreeAdaptor 
	{
	public:
		typedef KDTreeAdaptor<MatrixType, DIM, Distance> self_t;
		typedef typename MatrixType::Scalar	num_t;
		typedef typename MatrixType::Index	IndexType;
		typedef typename Distance::template traits<num_t, self_t>::distance_t metric_t;
		typedef nanoflann::KDTreeSingleIndexAdaptor< metric_t, self_t, DIM, IndexType>  index_t;
		
		index_t* index_; //! The kd-tree index for the user to call its methods as usual with any other FLANN index.
	
	private:
		const MatrixType* pmat_;

	public:
		/* Public interface */
		// Constructor: takes a const ref to the matrix object with the data points
		KDTreeAdaptor(const MatrixType &mat = MatrixType(), const int leaf_max_size = 10) :
			pmat_(nullptr), index_(nullptr)
		{
			setup(mat, leaf_max_size);			
		}

		inline void setup(const MatrixType &mat, const int leaf_max_size = 10)
		{
			const size_t dims = mat.rows();
			const size_t num = mat.cols();
			if (dims > 0 && num > 0)
			{
				pmat_ = &mat;
				if (index_) delete index_;
				index_ = new index_t(dims, *this, nanoflann::KDTreeSingleIndexAdaptorParams(leaf_max_size));
				index_->buildIndex();
			}
		}

		// destructor
		~KDTreeAdaptor() 
		{
			if (index_) delete index_;
		}
		
		// Query for the num_closest closest points to a given point (entered as query_point[0:dim-1]).
		inline void query(const num_t *query_point, const size_t num_closest, 
			IndexType *out_indices, num_t *out_distances_sq) const 
		{
			nanoflann::KNNResultSet<num_t, IndexType> resultSet(num_closest);
			resultSet.init(out_indices, out_distances_sq);
			index_->findNeighbors(resultSet, query_point, nanoflann::SearchParams());
		}

		// Query for the closest points to a given point (entered as query_point[0:dim-1]).
		inline void closest(const num_t *query_point, 
			IndexType *out_index, num_t *out_distance_sq) const
		{
			query(query_point, 1, out_index, out_distance_sq);
		}
		
		/* Interface expected by KDTreeSingleIndexAdaptor */
		const self_t & derived() const { return *this; }
		
		self_t & derived() { return *this; }
		
		// Must return the number of data points
		inline size_t kdtree_get_point_count() const { return pmat_->cols(); }
		
		// Returns the L2 distance between the vector "p1[0:size-1]"
		// and the data point with index "idx_p2" stored in the class:
		inline num_t kdtree_distance(const num_t *p1, const IndexType idx_p2, IndexType size) const 
		{
			num_t s = 0;
			for (IndexType i = 0; i < size; i++) {
				const num_t d = p1[i] - pmat_->coeff(i, idx_p2);
				s += d*d;
			}
			return s;
		}

		// Returns the dim'th component of the idx'th point in the class:
		inline num_t kdtree_get_pt(const IndexType idx, int dim) const 
		{
			return pmat_->coeff(IndexType(dim), idx);
		}

		// Optional bounding-box computation: return false to default to a standard bbox computation loop.
		template <class BBOX>
		bool kdtree_get_bbox(BBOX&) const { return false; }

	private:
		/** Hidden copy constructor, to disallow copying this class (Not implemented) */
		KDTreeAdaptor(const self_t&);
	};

	typedef KDTreeAdaptor<> KDTree;
}