/***
DEVSIM
Copyright 2013 Devsim LLC

This file is part of DEVSIM.

DEVSIM is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, version 3.

DEVSIM is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with DEVSIM.  If not, see <http://www.gnu.org/licenses/>.
***/

#include "TetrahedronElementField.hh"
#include "DenseMatrix.hh"
#include "EdgeModel.hh"
#include "Region.hh"
#include "Tetrahedron.hh"
#include "Edge.hh"
#include "TetrahedronEdgeModel.hh"
#include "dsAssert.hh"
#include "EdgeData.hh"
#include "Triangle.hh"

TetrahedronElementFieldMatrixHolder::TetrahedronElementFieldMatrixHolder()
{
  for (size_t i = 0; i < 4; ++i)
  {
    mats[i] = NULL;
    for (size_t j = 0; j < 3; ++j)
    {
      edgeIndexes[i][j] = 0;
    }
  }
}

TetrahedronElementFieldMatrixHolder::~TetrahedronElementFieldMatrixHolder()
{
  for (size_t i = 0; i < 4; ++i)
  {
    delete mats[i];
  }
}

TetrahedronElementField::~TetrahedronElementField()
{
}

TetrahedronElementField::TetrahedronElementField(const Region *r) : myregion_(r)
{
}

//// The matrices we develop are for each of the 4 nodes on the Tetrahedron
//// Each node has 3 edges connected to it
void TetrahedronElementField::CalcMatrices() const
{
  dsAssert(myregion_->GetDimension() == 3, "UNEXPECTED");
  //// TODO:Check for FPE's
  //// Assert fields exist
  ConstEdgeModelPtr ux = myregion_->GetEdgeModel("unitx");
  ConstEdgeModelPtr uy = myregion_->GetEdgeModel("unity");
  ConstEdgeModelPtr uz = myregion_->GetEdgeModel("unitz");

  dsAssert(ux.get(), "UNEXPECTED");
  dsAssert(uy.get(), "UNEXPECTED");
  dsAssert(uz.get(), "UNEXPECTED");

  const EdgeScalarList &xvec = ux->GetScalarValues();
  const EdgeScalarList &yvec = uy->GetScalarValues();
  const EdgeScalarList &zvec = uz->GetScalarValues();

//  const ConstTetrahedronList &tlist = myregion_->GetTetrahedronList();

  const ConstTetrahedronList &tetrahedronList = myregion_->GetTetrahedronList();

  const Region::TetrahedronToConstEdgeDataList_t &ttelist = myregion_->GetTetrahedronToEdgeDataList();

  ///// Need to handle 01, 02, 12 combinations
  dense_mats_.resize(tetrahedronList.size());

  for (size_t tindex = 0; tindex < tetrahedronList.size(); ++tindex)
  {
    const Tetrahedron   &tetrahedron = *tetrahedronList[tindex];

    const ConstEdgeDataList &edgeDataList = ttelist[tindex];

    const ConstNodeList  nodeList = tetrahedron.GetNodeList();

    double sx[3];
    double sy[3];
    double sz[3];
    size_t edgeIndexes[3];

    //// for each node
    //// find the four edges connected
    size_t k = 0;
    for (size_t i = 0; i < nodeList.size(); ++i)
    {
      k = 0;
      const ConstNodePtr nodeptr = nodeList[i];
      for (size_t j = 0; j < edgeDataList.size(); ++j)
      {
        const Edge &edge = *(edgeDataList[j]->edge);
        if ((edge.GetHead() == nodeptr) || (edge.GetTail() == nodeptr))
        {
          const size_t eindex = edge.GetIndex();
          edgeIndexes[k] = j;
          sx[k] = xvec[eindex];
          sy[k] = yvec[eindex];
          sz[k] = zvec[eindex];
          ++k;
        }
      }
      //// We expect to find 3 edges connected to this node
      dsAssert(k == 3, "UNEXPECTED");

      dsMath::RealDenseMatrix *dmp = new dsMath::RealDenseMatrix(3);
      dsMath::RealDenseMatrix &M = *dmp;

      for (size_t l = 0; l < 3; ++l)
      {
        M(l, 0) = sx[l];
        M(l, 1) = sy[l];
        M(l, 2) = sz[l];
      }

      bool info = M.LUFactor();
      dsAssert(info, "UNEXPECTED");
      dense_mats_[tindex].mats[i] = dmp;
      for (size_t m = 0; m < 3; ++m)
      {
        dense_mats_[tindex].edgeIndexes[i][m] = edgeIndexes[m];
      }
    }
  }
}

std::vector<Vector> TetrahedronElementField::GetTetrahedronElementField(const Tetrahedron &tetrahedron, const EdgeModel &em) const
{
  const size_t tetrahedronIndex = tetrahedron.GetIndex();
  const Region::TetrahedronToConstEdgeDataList_t &ttelist = myregion_->GetTetrahedronToEdgeDataList();
  const ConstEdgeDataList &edgeDataList = ttelist[tetrahedronIndex];

  const EdgeScalarList &evals = em.GetScalarValues();

  std::vector<double> edgedata(6);
  for (size_t i = 0; i < 6; ++i)
  {
    const size_t edgeIndex = (edgeDataList[i]->edge)->GetIndex();
    edgedata[i] = evals[edgeIndex];
  }

  return GetTetrahedronElementField(tetrahedron, edgedata);

}

std::vector<Vector> TetrahedronElementField::GetTetrahedronElementField(const Tetrahedron &tetrahedron, const TetrahedronEdgeModel &em) const
{
  const size_t tetrahedronIndex = tetrahedron.GetIndex();

  const TetrahedronEdgeScalarList &evals = em.GetScalarValues();

  std::vector<double> edgedata(6);
  for (size_t i = 0; i < 6; ++i)
  {
    const size_t edgeIndex = 6*tetrahedronIndex + i;
    edgedata[i] = evals[edgeIndex];
  }

  return GetTetrahedronElementField(tetrahedron, edgedata);

}

// TODO:"REVIEW CODE"
// TODO:"TEST CODE"
std::vector<Vector> TetrahedronElementField::GetTetrahedronElementField(const Tetrahedron &tetrahedron, const std::vector<double> &edgedata) const
{
  std::vector<Vector> ret(6);

  if (dense_mats_.empty())
  {
    CalcMatrices();
  }

  const size_t tetrahedronIndex = tetrahedron.GetIndex();

  //// this is the rhs vec
  std::vector<double> B(3);
  //// these are the values emanating from each node
  std::vector<Vector> nodeVectors(4);
  // for each node
  for (size_t i = 0; i < 4; ++i)
  {
    dsMath::RealDenseMatrix &M = *dense_mats_[tetrahedronIndex].mats[i];
    for (size_t j = 0; j < 3; ++j)
    {
      const size_t eindex = dense_mats_[tetrahedronIndex].edgeIndexes[i][j];
      ///// map local index to region edge index
      B[j] = edgedata[eindex];
    }

    bool info = M.Solve(B);
    dsAssert(info, "UNEXPECTED");

    //// This is the element field on one of the four nodes
    nodeVectors[i] = Vector(B[0], B[1], B[2]);
  }

  /// for each of the nodes
  for (size_t i = 0; i < 4; ++i)
  {
    const Vector &val = 0.5 * nodeVectors[i];

    //// calculate the average on the edge
    for (size_t j = 0; j < 3; ++j)
    {
      const size_t eindex = dense_mats_[tetrahedronIndex].edgeIndexes[i][j];

      //// use equal weighting for each node on the edge
      ret[eindex] += val;
    }
  }

  return ret;
}

//// em0 is the @n0
//// em1 is the @n1
//// return matrix is based as 2nd index as edge (0-5), 1st index as derivative w.r.t. node (0-3)
//// where 2 the first triangle node off edge and 3 is the 2nd triangle node off edge
//return as [nodeindex][edgeindex]
// TODO:"REVIEW CODE"
// TODO:"TEST CODE"
std::vector<std::vector<Vector> > TetrahedronElementField::GetTetrahedronElementField(const Tetrahedron &tetrahedron, const EdgeModel &em0, const EdgeModel &em1) const
{
  std::vector<std::vector<Vector> > ret(4);
  for (size_t i = 0; i < 4; ++i)
  {
    ret[i].resize(6);
  }

  if (dense_mats_.empty())
  {
    CalcMatrices();
  }

  const EdgeScalarList &evals0 = em0.GetScalarValues();
  const EdgeScalarList &evals1 = em1.GetScalarValues();

  const size_t tetrahedronIndex = tetrahedron.GetIndex();

  const ConstNodeList  nodeList = tetrahedron.GetNodeList();

  const Region::TetrahedronToConstEdgeDataList_t &ttelist = myregion_->GetTetrahedronToEdgeDataList();

  const ConstEdgeDataList &edgeDataList = ttelist[tetrahedronIndex];

  //// this is the rhs vec
  std::vector<double> B(3);
  //// these are the values emanating from each node

  Vector nodeVectors[4][4];
  /// foreach node index
  for (size_t i = 0; i < 4; ++i)
  {
//    const ConstNodePtr node_i_ptr = nodeList[i];

    dsMath::RealDenseMatrix &M = *dense_mats_[tetrahedronIndex].mats[i];
    // for each derivative index
    for (size_t j = 0; j < 4; ++j)
    {
      const ConstNodePtr node_j_ptr = nodeList[j];

      for (size_t k = 0; k < 3; ++k)
      {
        ConstEdgePtr edge_ptr = edgeDataList[k]->edge;

        const size_t edgeIndex = edge_ptr->GetIndex();

        ConstNodePtr nh = edge_ptr->GetHead();
        ConstNodePtr nt = edge_ptr->GetTail();

        double rhs = 0.0;
        if (nh == node_j_ptr)
        {
          rhs = evals0[edgeIndex];
        }
        else if (nt == node_j_ptr)
        {
          rhs = evals1[edgeIndex];
        }
        B[k] = rhs;
      }

      bool info = M.Solve(B);
      dsAssert(info, "UNEXPECTED");

      //// This is the element field on one of the four nodes
      nodeVectors[i][j] = Vector(B[0], B[1], B[2]);
    }
  }

  /// for each of the nodes
  for (size_t i = 0; i < 4; ++i)
  {
    /// for each of the derivatives
    for (size_t j = 0; j < 4; ++j)
    {
      const ConstNodePtr dnode = nodeList[j];

      const Vector &val = 0.5 * nodeVectors[i][j];

      //// calculate the average on the edge
      for (size_t k = 0; k < 3; ++k)
      {
        const size_t eindex = dense_mats_[tetrahedronIndex].edgeIndexes[i][k];

        ConstEdgePtr edge_ptr = edgeDataList[k]->edge;

//        const size_t edgeIndex = edge_ptr->GetIndex();

        //// This is the node on either end
        const ConstNodePtr nh = edge_ptr->GetHead();
        const ConstNodePtr nt = edge_ptr->GetTail();

        if (nh == dnode)
        {
          ret[0][eindex] += val;
        }
        else if (nt == dnode)
        {
          ret[1][eindex] += val;
        }
        else
        {
          ///// We are the nodes not on this edge
          ConstNodePtr triangle_nodes[2] = {NULL, NULL};
          for (size_t l = 0; l < 2; ++l)
          {
            //// TODO:
            //// Triangle to edge list makes guarantees that node index opposite to triangle edge index is not on edge
            //// For now we will do this hacky test
            const Triangle &triangle = *(edgeDataList[k]->triangle[l]);
            const ConstNodeList &nList = triangle.GetNodeList();
            for (size_t m = 0; m < 3; ++m)
            {
              const ConstNodePtr ntmp = nList[m];
              if (!((ntmp == nh) || (ntmp == nt)))
              {
                triangle_nodes[l] = ntmp;
                break;
              }  
            }
          }
          if (triangle_nodes[0] == dnode)
          {
            ret[2][eindex] += val;
          }
          else if (triangle_nodes[1] == dnode)
          {
            ret[3][eindex] += val;
          }
        }
      }
    }
  }

  return ret;
}

