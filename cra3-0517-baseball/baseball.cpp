#include <stdexcept>
#include <unordered_map>

using namespace std;

struct GuessResult {
	bool solved;
	int strikes;
	int balls;
};

class Baseball {
public:
	explicit Baseball(const string& question) : question(question) {
	}

	bool isDuplicatedNumber(const string& guessNumber) {
		return guessNumber[0] == guessNumber[1]
			|| guessNumber[0] == guessNumber[2]
			|| guessNumber[1] == guessNumber[2];
	}

	void assertIllegalArgument(const string& guessNumber) {
		if (guessNumber.length() != 3) {
			throw length_error("Must be three letters.");
		}

		for (char ch : guessNumber) {
			if (ch >= '0' && ch <= '9') continue;
			throw invalid_argument("Must be number");
		}

		if (isDuplicatedNumber(guessNumber))
			throw invalid_argument("Must not have the same number");
	}

	int countStrike(const std::string& guessNumber) {
		int strikes = 0;
		for (size_t i = 0; i < question.length(); ++i) {
			if (question[i] == guessNumber[i]) {
				++strikes;
			}
		}
		return strikes;
	}
	

	int countBall(const std::string& guessNumber) {
		unordered_map<char, int> questionMap;
		unordered_map<char, int> guessMap;

		for (size_t i = 0; i < question.length(); ++i) {
			if (question[i] == guessNumber[i]) continue;
			questionMap[question[i]]++;
			guessMap[guessNumber[i]]++;
		}

		int balls = 0;
		for (const auto& entry : guessMap) {
			char ch = entry.first;
			int countInGuess = entry.second;
			int countInQuestion = questionMap[ch];
			balls += min(countInGuess, countInQuestion);
		}

		return balls;
	}

	GuessResult guess(const string& guessNumber) {
		assertIllegalArgument(guessNumber);
		if (guessNumber == question) {
			return { true, 3, 0 };
		}
		else {
			return { false, countStrike(guessNumber), countBall(guessNumber) };
		}
	}

private:
	string question;

};
