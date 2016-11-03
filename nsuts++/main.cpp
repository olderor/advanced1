//  Created by olderor on 22.10.16.
//  Copyright © 2016 olderor. All rights reserved.

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

struct stream_manager {
public:
    static void read_int(std::istream &_Istr, int &data) {
        _Istr >> data;
    }

    static void read_vector(
        std::istream &_Istr, 
        std::vector<int> &vector, 
        const int size) {

        vector.clear();
        vector.resize(size);
        for (int i = 0; i < size; ++i) {
            _Istr >> vector[i];
        }
    }

    static void write_int(std::ostream &_Istr, const int data) {
        _Istr << data << std::endl;
    }
};

struct problem_solver {
public:
    static int solve(
        const int bus_count, 
        const int bus_capacity, 
        const int people_count, 
        const std::vector<int> people_weights) {

        const std::vector< std::vector<int> > weights_per_one_bus = 
            get_weights_per_one_bus(bus_capacity, people_count, people_weights);

        const std::vector< std::vector<int> > optimal_weights = 
            get_optimal_weights(bus_count, people_count, weights_per_one_bus);

        return optimal_weights[people_count - 1][bus_count - 1];
    }

private:
    static std::vector< std::vector<int> > get_weights_per_one_bus(
        const int bus_capacity, 
        const int people_count, 
        const std::vector<int> people_weights) {

        std::vector< std::vector<int> > weights_per_one_bus(
            people_count, std::vector<int>(people_count));

        for (int people_start_index = people_count - 1; 
            people_start_index >= 0; --people_start_index) {

            std::priority_queue<int> current_weights;
            int current_weights_sum = 0;
            int current_weights_size = 0;

            for (int people_end_index = people_start_index; 
                people_end_index < people_count; ++people_end_index) {

                if (people_weights[people_end_index] <= bus_capacity - current_weights_sum) {
                    current_weights.push(people_weights[people_end_index]);
                    current_weights_sum += people_weights[people_end_index];
                    ++current_weights_size;
                } else {
                    const int top = current_weights.top();
                    if (top > people_weights[people_end_index]) {
                        current_weights.pop();
                        current_weights.push(people_weights[people_end_index]);
                        current_weights_sum += people_weights[people_end_index] - top;
                    }
                }

                weights_per_one_bus[people_start_index][people_end_index] = current_weights_size;
            }
        }
        
        return weights_per_one_bus;
    }

    static std::vector< std::vector<int> > get_optimal_weights(
        const int bus_count, 
        const int people_count, 
        const std::vector< std::vector<int> > weights_per_one_bus) {

        std::vector< std::vector<int> > optimal_weights(people_count, 
            std::vector<int>(bus_count, 0));

        for (int j = 0; j < bus_count; ++j) {
            for (int i = people_count - 1; i >= 0; --i) {
                optimal_weights[i][j] = std::max(optimal_weights[i][j], weights_per_one_bus[0][i]);
                if (j == 0) {
                    continue;
                }
                for (int k = 0; k < i; ++k) {
                    optimal_weights[i][j] = std::max(optimal_weights[i][j],
                        optimal_weights[k][j - 1] + weights_per_one_bus[k + 1][i]);
                }
            }
        }

        return optimal_weights;
    }
};


void read_input(
    std::istream &_Istr,
    int &bus_count, 
    int &bus_capacity, 
    int &people_count, 
    std::vector<int> &people_weights) {

    stream_manager::read_int(_Istr, bus_count);
    stream_manager::read_int(_Istr, bus_capacity);
    stream_manager::read_int(_Istr, people_count);
    stream_manager::read_vector(_Istr, people_weights, people_count);
}

void write_output(std::ostream &_Istr, const int answer) {
    stream_manager::write_int(_Istr, answer);
}

int main() {

    // Making input and output faster.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int bus_count, people_count, bus_capacity;
    std::vector<int> people_weights;

    read_input(std::cin, bus_count, bus_capacity, people_count, people_weights);

    const int answer = problem_solver::solve(bus_count, bus_capacity, people_count, people_weights);

    write_output(std::cout, answer);

    return 0;
}
