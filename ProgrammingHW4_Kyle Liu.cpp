#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

class PageReplacement { //creates class of page replacement algorithms
private:
    vector<int> page_reference_string;
    int num_frames;
    vector<int> frames;
    int page_faults;

public:
    PageReplacement(vector<int> prs, int nf) : page_reference_string(prs), num_frames(nf), frames(), page_faults(0) {} //constructor

    void reset() { //function to reset internal state of page replacement object
        frames.clear();
        page_faults = 0;
    }

    void lru() { //function least recently used
    reset();
    unordered_map<int, int> page_table;
    for (int idx = 0; idx < page_reference_string.size(); ++idx) { //iterates through page reference string
        int page = page_reference_string[idx];
        if (find(frames.begin(), frames.end(), page) == frames.end()) {
            ++page_faults; //increments wgen page is accessed but not found in frame
            if (frames.size() < num_frames) {
                frames.push_back(page);
            } else { //adds to available empty frames
                int least_recently_used = frames[0];
                for (int i = 1; i < frames.size(); ++i) {
                    if (page_table[frames[i]] < page_table[least_recently_used]) {
                        least_recently_used = frames[i]; // adds to least recently used page in the frames 
                    }
                }
                frames[find(frames.begin(), frames.end(), least_recently_used) - frames.begin()] = page;
            }
            page_table[page] = idx;
        } else {
            page_table[page] = idx; //maintains page table 
        }
        cout << "Step " << idx + 1 << ": Page fault (" << page << ") - Page Table: {";
        for (auto& entry : page_table) {
            cout << entry.first << " ";
        }
        cout << "}, Frames: [";
        for (int i = 0; i < frames.size(); ++i) {
            cout << frames[i];
            if (i != frames.size() - 1) {
                cout << ", ";
            }
        }
        cout << "], Faults: " << page_faults << endl;
    }
    cout << "Total Page Faults: " << page_faults << endl;
}

    void optimal() { //function for optimal page replacement 
        reset();
        for (int idx = 0; idx < page_reference_string.size(); ++idx) { // iterates through page reference string
            int page = page_reference_string[idx];
            if (find(frames.begin(), frames.end(), page) == frames.end()) {
                ++page_faults; //page fault occurs when a page is accessed but not found in frame
                if (frames.size() < num_frames) {
                    frames.push_back(page);
                } else { // if frames are full function predicts which frame will not be used for the longest time
                    unordered_map<int, int> future_indices;
                    for (int i = 0; i < frames.size(); ++i) {
                        auto it = find(page_reference_string.begin() + idx, page_reference_string.end(), frames[i]);
                        future_indices[frames[i]] = (it != page_reference_string.end()) ? distance(page_reference_string.begin(), it) : INT_MAX;
                    }
                    int page_to_replace = max_element(future_indices.begin(), future_indices.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
                        return a.second < b.second; //maintains a future indices map to store the indices of future accesses
                    })->first;
                    frames[find(frames.begin(), frames.end(), page_to_replace) - frames.begin()] = page;
                }
            }
            cout << "Step " << idx + 1 << ": Page fault (" << page << ") - Page Table: {";
            for (auto& frame : frames) {
                cout << frame << " ";
            }
            cout << "}, Frames: [";
            for (int i = 0; i < frames.size(); ++i) {
                cout << frames[i];
                if (i != frames.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "], Faults: " << page_faults << endl;
        }
        cout << "Total Page Faults: " << page_faults << endl;
    }

    void fifo() { //function simulates the First In First Out (FIFO) page replacement algorithm.
        reset();
        queue<int> page_queue;
        for (int idx = 0; idx < page_reference_string.size(); ++idx) { //iterates through the page reference string.
            int page = page_reference_string[idx];
            if (find(frames.begin(), frames.end(), page) == frames.end()) {
                ++page_faults; //when a page is accessed and not found in the frames increments the page_faults counter
                if (frames.size() < num_frames) { // available empty frames the new page is simply added to the frames.
                    frames.push_back(page);
                    page_queue.push(page);
                } else { //if frames are full, the function replaces the oldest page in the frames based on the order in which pages were brought into memory by using a queue
                    int oldest_page = page_queue.front();
                    page_queue.pop();
                    frames[find(frames.begin(), frames.end(), oldest_page) - frames.begin()] = page;
                    page_queue.push(page);
                }
            }
            cout << "Step " << idx + 1 << ": Page fault (" << page << ") - Page Table: {";
            for (auto& frame : frames) {
                cout << frame << " ";
            }
            cout << "}, Frames: [";
            for (int i = 0; i < frames.size(); ++i) {
                cout << frames[i];
                if (i != frames.size() - 1) {
                    cout << ", ";
                }
            }
            cout << "], Faults: " << page_faults << endl;
        }
        cout << "Total Page Faults: " << page_faults << endl;
    }
};

int main() {
    vector<int> page_reference_string = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5}; //creates a vector with the reference string
    int num_frames = 4; //sets the number of frames

    cout << "For LRU Algorithm:" << endl; 
    PageReplacement lru_simulator(page_reference_string, num_frames); //calls the function lru
    lru_simulator.lru();

    cout << "\nFor Optimal Algorithm:" << endl;
    PageReplacement optimal_simulator(page_reference_string, num_frames);//calls the function optimal
    optimal_simulator.optimal();

    cout << "\nFor FIFO Algorithm:" << endl;
    PageReplacement fifo_simulator(page_reference_string, num_frames);// calls the function fifo
    fifo_simulator.fifo();

    return 0;
}

