#include <iostream>
#include <vector>
#include <string>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe { //물약 1개의 정보 이름 +재료목록
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 재료가 여러개라서 vector

    // 매개변수 (name, ingredients) 멤버 변수 (potionName, ingredients)
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리
class AlchemyWorkshop {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    void addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
        if (recipes.empty()) {
            std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
            return;
        }

        std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
        for (size_t i = 0; i < recipes.size(); ++i) {
            std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
            std::cout << "  > 필요 재료: ";

            // 재료 목록을 순회하며 출력
            for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
                std::cout << recipes[i].ingredients[j];
                // 마지막 재료가 아니면 쉼표로 구분
                if (j < recipes[i].ingredients.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
        std::cout << "---------------------------\n";
    }

    PotionRecipe searchRecipeByName(const std::string& name) const //이름 검색
    {
        for (const auto& recipe : recipes) { //recipe -> Potion Recipe 객체 하나
            if (recipe.potionName == name) {
                return recipe;
            }
     }
        return PotionRecipe("찾으시는거 없어요", {});
              
    }

    // 특정 재료가 들어간 모든 물약을 찾아서 돌려준다
    std::vector<PotionRecipe> searchRecipeByIngredient(const std::string& ingredient) const //재료 검색
    {
        std::vector<PotionRecipe> result;//모르겠음 따로 공부 해야할듯
      //물약 재료로 검색이 가능 / 특정 재료가 포함된 모든 레시피를 찾을 수 있어야 함
        for (const auto& recipe : recipes) //물약 확인
        {
            for (const auto& i : recipe.ingredients) //그 물약의 재료 하나씩 확인
            {
                if (i == ingredient) { //재료 이름이 같으면
                    result.push_back(recipe); //맨위에 추가해준다 
                    break; //중복 방지
                }
            }
        }

        return result;
        /* 결과가 1개일 수 도 없을 수 도 여러 개일 수도 있으니 vector형이 필요하고
        하나만 찾을 때는 바로 return하면 되지만 여러개를 찾아야하니 
        result를 vector형 PotionRecipe형 으로 선언해줘서  result에 찾아낸 물약들을 담아낸다?
        */
    }



};

int main() {
    AlchemyWorkshop myWorkshop;

    myWorkshop.addRecipe("체력 포션", std::vector<std::string>{"허브"});
    myWorkshop.addRecipe("마나 포션", std::vector<std::string>{"마법의 물"});
    myWorkshop.addRecipe("스테미나 포션", std::vector<std::string>{"허브"});
    myWorkshop.addRecipe("불속성 저항 포션", std::vector<std::string>{"화염꽃"});
   //AlchemyWorkShop 클래스에 들어가있다.


    while (true) {
        std::cout << "연금술 공방 관리 시스템" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 검색" << std::endl;
        std::cout << "4. 재료 이름으로 검색" << std::endl;
        std::cout << "5. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                myWorkshop.addRecipe(name, ingredients_input);
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            myWorkshop.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string searchName;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, searchName);
            
            PotionRecipe result = myWorkshop.searchRecipeByName(searchName);

            std::cout << result.potionName << ", ";
            for (const auto& ing : result.ingredients) {
                std::cout << ing << " ";
            }  
            std::cout <<std::endl;
        }

        else if (choice == 4) {
            std::string searchIngredientName;
            std::cout << "재료 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, searchIngredientName);

            ?? result = myWorkshop.searchRecipeByIngredient(searchIngredientName); //무엇을 넣어야할지...

            for (const auto& ing : recipe.potionName) {

                std::cout << recipe.potionName << std::endl; //정의를 이상하게 한듯. recipe : recipe.potionName으로 하거나 ing에 맞게 하거나
            }
        }


        else if (choice == 5) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}
