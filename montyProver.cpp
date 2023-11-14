#include <iostream>
#include <random>

int main() {
    int car = 0, goat = 0;  // 차를 얻은 수, 염소를 얻은 수
    int caseTemp = 100000;  // 시도 횟수
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 2);

    for (int i = 0; i < caseTemp; i++) {
        int doors[3] = {0, 0, 0};  // 문 (0은 염소, 1은 자동차)
        int answer = dis(gen);     // 자동차가 있는 문
        doors[answer] = 1;
        int pickers_choice = dis(gen);  // 참가자의 선택

        int moderator_showup_choice;  // 사회자가 보여줄 문
        if (pickers_choice == answer) {
            do {
                moderator_showup_choice = dis(gen);
            } while (moderator_showup_choice == pickers_choice);
        } else {
            for (int j = 0; j < 3; j++) {
                if (j != pickers_choice && j != answer) {
                    moderator_showup_choice = j;
                    break;
                }
            }
        }

        // 참가자가 선택을 바꿉니다
        for (int j = 0; j < 3; j++) {
            if (j != pickers_choice && j != moderator_showup_choice) {
                pickers_choice = j;
                break;
            }
        }

        // 최종 결과 계산
        if (pickers_choice == answer) {
            car++;
        } else {
            goat++;
        }
    }

    double percent_car = static_cast<double>(car) / caseTemp * 100.0;
    double percent_goat = static_cast<double>(goat) / caseTemp * 100.0;
    std::cout << "자동차: " << percent_car << "%" << std::endl;
    std::cout << "염소: " << percent_goat << "%" << std::endl;

    return 0;
}
