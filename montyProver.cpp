#include <iostream>
#include <random>
int main() {
    int clear = 0;      // 한번에 맞춘 수 (테스트 용으로 넣음)
    int car, goat = 0;  // 차를 얻은 수, 염소를 얻은 수.
    int caseTemp = 1000000;  // 시도 얼마나 할건지
    for (int i = 0; i < caseTemp; i++) {
        // 문에 차를 넣고, 하나를 고릅니다.
        int doors[3] = {0, 0, 0};  // 문 (0은 염소, 1은 자동차)
        int pickers_choice = 0;    // 나의 선택
        int answer = 0;            // 자동차가 있는 문

        // 자동차가 들어있는 문, 나의 선택을 랜덤으로
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 2);
        answer = dis(gen);
        doors[answer] = 1;
        pickers_choice = dis(gen);

        // 만약 바로 차가 나오면 clear를 올립니다. 33.3% 에 가까울수록 난수
        // 생성기의 결백을 증명함.
        int moderator_showup_choice =
            0;  // 진행자가 어느 문의 염소를 보여줄 지 정하는 변수
        if (doors[pickers_choice] ==
            1) {  // 만약 한번에 맞췄다면 clear++ 하고 계속 진행 (뽑는 사람은
                  // 아직 자기가 정답을 지목한걸 모름)
            clear++;
        }

        // 사회자가 염소를 하나 보여줍니다
        bool change = true;  // true면 picker가 선택지를 바꿈
        int temp[3] = {0, 1, 2};  // 0, 1, 2번째 문중에 어느 문을 선택할지
                                  // 고르기 위해 선언한 임시 변수
        if (pickers_choice == answer) {  // 만약 picker가 정답을 지목한 상태라면
            bool go = true;
            while (go) {  // picker의 선택을 제외한 나머지 두개의 문 중에 하나를
                          // 랜덤으로 뽑아서 사회자가 보여줍니다.
                int genTemp = 0;
                genTemp = dis(gen);
                if (genTemp != answer) {
                    moderator_showup_choice = genTemp;
                    go = false;
                    break;
                }
            }
        } else {  // 만약 picker가 정답을 지목하지 못했으면
            for (int i = 0; i < 3;
                 i++) {  // 나머지 두개의 문 중 염소가 있는 문을 보여줍니다
                if (temp[i] != answer && temp[i] != pickers_choice)
                    moderator_showup_choice = i;
            }
        }
        // moderator가 염소를 보여준다!!!
        std::cout << moderator_showup_choice + 1 << "번째 문에 염소가 있습니다."
                  << std::endl;

        if (change) {  // 선택을 바꾼다면
            for (int i = 0; i < 3;
                 i++) {  // picker는 내 선택지와 사회자가 보여준 문을 제외하고
                         // 남은 나머지 하나의 문으로 선택을 바꿉니다.
                if (temp[i] != pickers_choice &&
                    temp[i] != moderator_showup_choice) {
                    pickers_choice = i;
                }
            }
        } else {  // 선택을 바꾸지 않는다면 그대로 진행
        }

        // 마지막 계산
        if (pickers_choice == answer)
            car++;
        else
            goat++;
    }
    double percent_car = (static_cast<double>(car) / caseTemp) * 100.0;
    double percent_goat = (static_cast<double>(goat) / caseTemp) * 100.0;
    std::cout << "자동차: " << percent_car << "%" << std::endl;
    std::cout << "염소: " << percent_goat << "%" << std::endl;
    return 0;
}
