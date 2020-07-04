#pragma once
#include "cupoch/geometry/geometry.h"
#include "cupoch/utility/device_vector.h"
#include "cupoch/utility/eigen.h"

namespace cupoch {
namespace geometry {

/// Get Rotation Matrix from XYZ RotationType.
Eigen::Matrix3f GetRotationMatrixFromXYZ(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from YZX RotationType.
Eigen::Matrix3f GetRotationMatrixFromYZX(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from ZXY RotationType.
Eigen::Matrix3f GetRotationMatrixFromZXY(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from XZY RotationType.
Eigen::Matrix3f GetRotationMatrixFromXZY(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from ZYX RotationType.
Eigen::Matrix3f GetRotationMatrixFromZYX(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from YXZ RotationType.
Eigen::Matrix3f GetRotationMatrixFromYXZ(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from AxisAngle RotationType.
Eigen::Matrix3f GetRotationMatrixFromAxisAngle(const Eigen::Vector3f &rotation);
/// Get Rotation Matrix from Quaternion.
Eigen::Matrix3f GetRotationMatrixFromQuaternion(
        const Eigen::Vector4f &rotation);

template <int Dim>
Eigen::Matrix<float, Dim, 1> ComputeMinBound(
        const utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);
template <int Dim>
Eigen::Matrix<float, Dim, 1> ComputeMinBound(
        cudaStream_t stream,
        const utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);

template <int Dim>
Eigen::Matrix<float, Dim, 1> ComputeMaxBound(
        const utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);
template <int Dim>
Eigen::Matrix<float, Dim, 1> ComputeMaxBound(
        cudaStream_t stream,
        const utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);
template <int Dim>
Eigen::Matrix<float, Dim, 1> ComputeCenter(
        const utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);

void ResizeAndPaintUniformColor(utility::device_vector<Eigen::Vector3f> &colors,
                                const size_t size,
                                const Eigen::Vector3f &color);

/// \brief Transforms all points with the transformation matrix.
///
/// \param transformation 4x4 matrix for transformation.
/// \param points A list of points to be transformed.
template <int Dim>
void TransformPoints(
        const Eigen::Matrix<float, Dim + 1, Dim + 1> &transformation,
        utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);
template <int Dim>
void TransformPoints(
        cudaStream_t stream,
        const Eigen::Matrix<float, Dim + 1, Dim + 1> &transformation,
        utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points);
/// \brief Transforms the normals with the transformation matrix.
///
/// \param transformation 4x4 matrix for transformation.
/// \param normals A list of normals to be transformed.
void TransformNormals(const Eigen::Matrix4f &transformation,
                      utility::device_vector<Eigen::Vector3f> &normals);
void TransformNormals(cudaStream_t stream,
                      const Eigen::Matrix4f &transformation,
                      utility::device_vector<Eigen::Vector3f> &normals);
/// \brief Apply translation to the geometry coordinates.
///
/// \param translation A 3D vector to transform the geometry.
/// \param points A list of points to be transformed.
/// \param relative If `true`, the \p translation is directly applied to the
/// \points. Otherwise, the center of the \points is moved to the \p
/// translation.
template <int Dim>
void TranslatePoints(
        const Eigen::Matrix<float, Dim, 1> &translation,
        utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points,
        bool relative);
/// \brief Scale the coordinates of all points by the scaling factor \p
/// scale.
///
/// \param scale If `true`, the scale is applied relative to the center of
/// the geometry. Otherwise, the scale is directly applied to the geometry,
/// i.e. relative to the origin. \param points A list of points to be
/// transformed. \param center If `true`, then the scale is applied to the
/// centered geometry.
template <int Dim>
void ScalePoints(const float scale,
                 utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points,
                 bool center);
/// \brief Rotate all points with the rotation matrix \p R.
///
/// \param R A 3D vector that either defines the three angles for Euler
/// rotation, or in the axis-angle representation the normalized vector
/// defines the axis of rotation and the norm the angle around this axis.
/// \param points A list of points to be transformed.
/// \param center If `true`, the rotation is applied relative to the center
/// of the geometry. Otherwise, the rotation is directly applied to the
/// geometry, i.e. relative to the origin.
template <int Dim>
void RotatePoints(const Eigen::Matrix<float, Dim, Dim> &R,
                  utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points,
                  bool center);
template <int Dim>
void RotatePoints(cudaStream_t stream,
                  const Eigen::Matrix<float, Dim, Dim> &R,
                  utility::device_vector<Eigen::Matrix<float, Dim, 1>> &points,
                  bool center);
/// \brief Rotate all normals with the rotation matrix \p R.
///
/// \param R A 3D vector that either defines the three angles for Euler
/// rotation, or in the axis-angle representation the normalized vector
/// defines the axis of rotation and the norm the angle around this axis.
/// \param normals A list of normals to be transformed.
void RotateNormals(const Eigen::Matrix3f &R,
                   utility::device_vector<Eigen::Vector3f> &normals);
void RotateNormals(cudaStream_t stream,
                   const Eigen::Matrix3f &R,
                   utility::device_vector<Eigen::Vector3f> &normals);

}  // namespace geometry
}  // namespace cupoch