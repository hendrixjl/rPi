#include "imu.h"
#include "stdout.h"
#include "timeUtils.h"


using namespace Eigen;

enum {
	LSM303_A=0x19,
	LSM303_M=0x1E,
	L3GD20=0x6B
};

imu::imu(i2c& ani2c)
: gyro_(L3GD20, ani2c),
  accelerometer_(LSM303_A, ani2c),
  magnetometer_(LSM303_M, ani2c),
  heading_(0.0),
  inclination_(0.0),
  roll_(0.0)
{
	gyro_.enable();
	accelerometer_.enable();
	magnetometer_.enable();
}

imu::~imu()
{
}

void imu::integrate()
{
	cout << getTime() << ",";
	int16_t angles[3];
	int16_t accels[3] = {};
	int16_t mags[3] = {};

    gyro_.getAngles(angles);
	accelerometer_.getAcc(accels);
	magnetometer_.getMag(mags);

	cout << angles[1] << ',';
	cout << angles[2] << ',';

	cout << accels[0] << ',';
	cout << accels[1] << ',';
	cout << accels[2] << ',';

	cout << mags[0] << ',';
	cout << mags[1] << ',';
	cout << mags[2] << ',';
}

Matrix3f imu::rotationFromCompass(const Vector3f& acceleration, const Vector3f& magnetic_field)
{
	Vector3f down = -acceleration;     // usually true
	Vector3f east = down.cross(magnetic_field); // actually it's magnetic east
	Vector3f north = east.cross(down);

    east.normalize();
    north.normalize();
    down.normalize();

    Matrix3f r;
    r.row(0) = north;
    r.row(1) = east;
    r.row(2) = down;
    return r;
}


void imu::fuse_compass_only(Quaternionf& rotation, float dt, const Vector3f& angular_velocity,
  const Vector3f& acceleration, const Vector3f& magnetic_field)
{
    // Implicit conversion of rotation matrix to quaternion.
    rotation = rotationFromCompass(acceleration, magnetic_field);
}

// Uses the given angular velocity and time interval to calculate
// a rotation and applies that rotation to the given quaternion.
// w is angular velocity in radians per second.
// dt is the time.
void imu::rotate(Quaternionf& rotation, const Vector3f& w, float dt)
{
    // Multiply by first order approximation of the
    // quaternion representing this rotation.
    rotation *= Quaternionf(1, w(0)*dt/2, w(1)*dt/2, w(2)*dt/2);
    rotation.normalize();
}

void imu::fuse_gyro_only(Quaternionf& rotation, float dt, const Vector3f& angular_velocity,
  const Vector3f& acceleration, const Vector3f& magnetic_field)
{
    rotate(rotation, angular_velocity, dt);
}

void imu::fuse_default(Quaternionf& rotation, float dt, const Vector3f& angular_velocity,
  const Vector3f& acceleration, const Vector3f& magnetic_field)
{
    Vector3f correction(0, 0, 0);

    if (abs(acceleration.norm() - 1) <= 0.3)
    {
        // The magnetidude of acceleration is close to 1 g, so
        // it might be pointing up and we can do drift correction.

        const float correction_strength = 1;

        Matrix3f rotationCompass = rotationFromCompass(acceleration, magnetic_field);
        Matrix3f rotationMatrix = rotation.toRotationMatrix();

        correction = (
            rotationCompass.row(0).cross(rotationMatrix.row(0)) +
            rotationCompass.row(1).cross(rotationMatrix.row(1)) +
            rotationCompass.row(2).cross(rotationMatrix.row(2))
          ) * correction_strength;

    }

    rotate(rotation, angular_velocity + correction, dt);
}

