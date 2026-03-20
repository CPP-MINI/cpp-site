#pragma once

#include <string>
#include <vector>
#include <variant>
#include <optional>
#include <iostream>
#include <numeric>
#include <algorithm>
#include <cmath>

template <typename T>
class Sensor {
public:
	struct Identity {
		std::string hardwareID;
		std::string type;
		Identity(std::string id, std::string type) : hardwareID(std::move(id)), type(std::move(type)) {}
	};

private:
	std::string label;
	std::variant<Identity, std::string> source;
	std::optional<std::string> unit;
	std::vector<T> measurements;

public:
	Sensor(std::string label, std::variant<Identity, std::string> source, std::optional<std::string> unit = std::nullopt)
		: label(std::move(label)), source(std::move(source)), unit(std::move(unit)) {
	}

	const std::string& getLabel() const { return label; }
	const std::variant<Identity, std::string>& getSource() const { return source; }
	const std::optional<std::string>& getUnit() const { return unit; }
	const std::vector<T>& getMeasurements() const { return measurements; }

	T getRMS() const {
		if (measurements.empty()) return T(0);
		T sumSq = std::accumulate(measurements.begin(), measurements.end(), T(0), [](T acc, T val) {
			return acc + val * val;
			});
		return std::sqrt(sumSq / measurements.size());
	}

	T getMin() const {
		if (measurements.empty()) return T(0);
		return *std::min_element(measurements.begin(), measurements.end());
	}

	bool operator>(const Sensor& other) const {
		return label > other.label || (label == other.label && measurements.size() > other.measurements.size());
	}

	bool operator!=(const Sensor& other) const {
		return label != other.label;
	}

	Sensor& operator<<(T reading) {
		measurements.push_back(reading);
		return *this;
	}

	std::ostream& writeToStream(std::ostream& os) const {
		os << label << " [";
		if (std::holds_alternative<Identity>(source)) {
			const auto& meta = std::get<Identity>(source);
			os << meta.hardwareID << ", " << meta.type;
		}
		else {
			os << std::get<std::string>(source);
		}
		os << "] RMS: " << getRMS() << ", Min: " << getMin() << "\n";
		if (unit) {
			os << "Unit: " << *unit << "\n";
		}
		return os;
	}
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Sensor<T>& s) {
	return s.writeToStream(os);
}