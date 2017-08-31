#ifndef MOTORCOM_IMPL_RS01_HPP
#define MOTORCOM_IMPL_RS01_HPP

#include <net/if.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h> 	//For sockets

#include "../../5_DataType/RowEnum.hpp"
#include "_MotorCommunicatorInterface.hpp"

class MotorComRS01Impl: public MotorCommunicatorInterface {

public:
	MotorComRS01Impl(Row r);
	void linearMovement(int position);
	void rotate(int amount);

protected:
	void driverInit();
};

#endif //MOTORCOM_IMPL_PS01_HPP