#include <iostream>

//	 ///
//	<* \__/
//	 \___/
//	  _|

int main() {

	float s = 300.0f, u = 0.0f, t, a = 9.8, l = 0.0f;

	//while (s < 600) {
	//	s = (u * t) + (a * std::pow(t, 2));
	//	t += 0.00001;
	//}

	t = std::sqrt(2*s/a);

	printf("T: %f\n", t);
	printf("Non-death Time: %f\n", t - 2.0f);
	printf("Non-death Velocity: %f\n", (a * (t - 2)));


	while (l < t-2) {
		s = (a/2 * std::pow(t, 2));
		l += 0.5;
		printf("Velocity: %f at Time: %f\n", (a * l), l);
	}

	system("pause");
	return 0x0;
}
// s=300
// a=9.8
// t=??

//s=1/2