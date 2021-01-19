#include "poly.hpp"

std::list<Term> Poly::getTerms() const { return terms; }

bool Poly::append(Term &input) {

  // Handle if terms are empty
  if (terms.empty()) {
    terms.push_back(input);
    return true;
  }

  // Saving input data to reduce function calls
  const std::string inputVariable = input.getVariable();
  const int inputCoefficient = input.getCoefficient();
  double inputExponent = input.getExponent();

  if (inputExponent < 0) {
    inputExponent *= -10000;
  } else if (inputExponent < 1 && inputExponent > 0) {
    inputExponent *= 100;
  }
  int prevExponent = std::numeric_limits<int>::max();
  auto i = terms.begin();
  // Looping through each member of terms
  for (; i != terms.end(); ++i) {

    // Saving i data to reduce function calls
    auto &curr = *i;
    const std::string currVariable = curr.getVariable();
    double currExponent = curr.getExponent();

    if (currExponent < 0) {
      currExponent *= -10000;
    } else if (currExponent < 1 && currExponent > 0) {
      currExponent *= 100;
    }
    // Check if variables are the same
    if (inputVariable == currVariable) {

      // Adding to the coefficient if exponents are the same
      if (inputExponent == currExponent) {
        curr.addCoefficient(inputCoefficient);
        return true;
      }
    }

    // Checks if prevExponent > inputExponent > currExponent which means that
    // it should be added in between
    if (prevExponent > inputExponent && currExponent < inputExponent) {
      terms.insert(i, input);
      return true;
    }

    prevExponent = currExponent;
  }

  if (i == terms.end()) {
    terms.push_back(input);
    return true;
  }

  return false;
}

bool Poly::multiply(Term &input) {
  for (auto &i : terms) {
    if (i.multiplyTerm(input) == false) {
      return false;
    }
  }

  return true;
}

bool Poly::divide(int divisor) {
  if (divisor == 1) {
    return true;
  } else {
    for (auto &i : terms) {
      if (i.divide(divisor) == false) {
        return false;
      }
    }
  }
  return true;
}
// Apply summation to all members of the polynomial
bool Poly::applySummation(bool isUpperLimitNumber, bool isLogarithmic,
                          bool isRoot, int lowerLimit, int upperLimitInt,
                          std::string upperLimitString) {
  for (auto it = terms.begin(); it != terms.end(); it++) {

    // If upper limit is not a number and the lower limit is != 1, a formula is
    // applied to get the summation
    if ((!isUpperLimitNumber || isLogarithmic) && lowerLimit != 1) {

      // Create new term for the constant part of the formula
      Term newTerm(0 - it->getCoefficient(), it->getExponent());

      // apply summation to both
      it->applySummation(isUpperLimitNumber, isLogarithmic, isRoot, 1,
                         upperLimitInt, upperLimitString);
      newTerm.applySummation(true, false, false, 1, lowerLimit - 1, "");

      // Append new term
      this->append(newTerm);

      // skips the next term
      it++;
    } else {

      // If upper limit is a number, normal summation rules are applied
      if (it->applySummation(isUpperLimitNumber, isLogarithmic, isRoot,
                             lowerLimit, upperLimitInt,
                             upperLimitString) == false) {
        return false;
      }
    }
  }

  return true;
}

// Prints the terms
void Poly::printTerms() const {
  if (terms.front().getIsInfinite()) {
    std::cout << "infinite" << std::endl;
  } else {
    for (auto i = terms.begin(); i != terms.end(); ++i) {
      auto &curr = *i;
      const int currCoefficient = curr.getCoefficient();
      const int currCoefficientDenominator = curr.getCoefficientDenominator();
      const double currExponent = curr.getExponent();
      const std::string currVariable = curr.getVariable();

      std::string currVariableString = "";
      std::string currCoefficientString = "";
      std::string currRootString = "";
      std::ostringstream currExponentObj;
      currExponentObj << std::setprecision(2) << currExponent;

      // Handle all variable printing depending on exponent
      if (currExponent > 1) {
        currVariableString = currVariable + "^" + currExponentObj.str();
      } else if (currExponent == 1 || currExponent < 0) {
        currVariableString = currVariable;
      } else if (currExponent < 1 && currExponent > 0) {
        const double currExponentTemp = 1.0 / currExponent;
        switch (static_cast<int>(currExponentTemp)) {
        case 2:
          currRootString = " sqrt(";
          break;
        case 3:
          currRootString = " cubert(";
          break;
        case 4:
          currRootString = " fourthrt(";
          break;
        case 5:
          currRootString = " fifthrt(";
          break;
        case 6:
          currRootString = " sixthrt(";
          break;
        case 7:
          currRootString = " seventhrt(";
          break;
        case 8:
          currRootString = " eightrt(";
          break;
        case 9:
          currRootString = " nintht(";
          break;
        }
        currVariableString = currVariable;
      }

      // Handle coefficient printing
      if (currCoefficientDenominator == 1) {
        currCoefficientString = std::to_string(std::abs(currCoefficient));
      } else if (currCoefficientDenominator > 1) {
        currCoefficientString = std::to_string(std::abs(currCoefficient)) +
                                currVariableString + "/" +
                                std::to_string(currCoefficientDenominator);
        currVariableString = "";
      }

      // Handle prepending + or - depending on sign
      if (i != terms.begin()) {
        std::cout << ((currCoefficient < 0) ? " - " : " + ");
      } else {
        std::cout << ((currCoefficient < 0) ? "-" : "");
      }

      if (currExponent < 0) {
        std::cout << currCoefficientString << " log(" << std::abs(currExponent)
                  << ") " << currVariableString;
      } else if (currExponent > 0 && currExponent < 1) {
        std::cout << currCoefficientString << currRootString
                  << currVariableString << ")";
      } else {
        std::cout << currCoefficientString << currVariableString;
      }
    }

    std::cout << std::endl;
  }
}
