#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>

#include "disjoint_set.cpp"

struct p6_image {
    unsigned char ***rgb;
    int width,
        height;
};

struct p6_image * read_P6(const char*);
int is_same_color(unsigned char*, unsigned char*);
void print_vectors(disjoint_set, int);

int main(int argc, char ** argv) {
    struct p6_image *image = read_P6("../simple_image_make/image.pgm");

    if (image == 0)
        return 0;
    
    int matches = 0;

    char c;

    disjoint_set ds = disjoint_set(image->width * image->height);

    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            for (int k = 0; k < 3; k++) {
                // std::cout << std::setw(3);
                // if (k != 2)
                //     std::cout << (int) image->rgb[i][j][k] << ",";
                // else
                //     std::cout << (int) image->rgb[i][j][k];
            }

            std::cout << "Current location: (" << i << "," << j << ")\n";
            std::cout << "\tCurrent parent: " << ds.find(i * image->width + j) << "\n";
            std::cout << "\tCurrent color: (" << (int) image->rgb[i][j][0] << ","
                << (int) image->rgb[i][j][1] << ","
                << (int) image->rgb[i][j][2] << ")\n";

            if (i+1 < image->height) {
            std::cout << "\ti+1 parent: " << ds.find((i+1) * image->width + j) << "\n";
            std::cout << "\ti+1 color: (" << (int) image->rgb[i+1][j][0] << ","
                << (int) image->rgb[i+1][j][1] << ","
                << (int) image->rgb[i+1][j][2] << ")\n";
            }

            if (j+1 < image->width) {
                std::cout << "\tj+1 parent: " << ds.find(i * image->width + j + 1) << "\n";
                std::cout << "\tj+1 color: (" << (int) image->rgb[i][j+1][0] << ","
                    << (int) image->rgb[i][j+1][1] << ","
                    << (int) image->rgb[i][j+1][2] << ")\n";
            }

            if ((i+1 < image->height) && (ds.find(i * image->width + j) != ds.find((i+1) * image->width + j)) && (is_same_color(image->rgb[i][j], image->rgb[i+1][j]))) {
                ds.join_by_size(i * image->width + j, (i+1) * image->width + j);
                std::cout << "\tFound match in i+1\n";
                matches++;
            }
            if ((j+1 < image->width) && (ds.find(i * image->width + j) != ds.find(i * image->width + j + 1)) && (is_same_color(image->rgb[i][j], image->rgb[i][j+1]))) {
                ds.join_by_size(i * image->width + j, i * image->width + j + 1);
                std::cout << "\tFound match in j+1\n";
                matches++;
            }

            print_vectors(ds, image->width * image->height);

            std::cin.get();
        }
    }

    std::cout << "Matches found: " << matches << "\n";

    print_vectors(ds, image->width * image->height);

    int found = 0;
    std::vector<int> parents;

    for (int i = 0; i < ds.sets.size(); i++) {
        found = 0;
        for (int j = 0; j < parents.size(); j++) {
            if (ds.find(ds.sets[i]) == parents[j]) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            parents.push_back(ds.find(ds.sets[i]));
        }
    }

    for (int i = 0; i < parents.size(); i++) {
        std::cout << parents[i];
        if (i+1 < parents.size())
            std::cout << ", ";
    }
    std::cout << "\n";

    return 0;
}

struct p6_image * read_P6(const char* name) {
    if (name == 0)
        return 0;

    struct p6_image *image = new p6_image;

    std::ifstream i_f = std::ifstream(name, std::ios::binary);

    if (!i_f) {
        std::cout << "Error while making i_f.\n";
        return 0;
    }

    unsigned char c;
    int width,
        height,
        max_value;

    i_f >> c >> c >> width >> height >> max_value;
    i_f.get();

    std::cout << "c: " << c << "\n";
    std::cout << "width: " << width << "\n";
    std::cout << "height: " << height << "\n";
    std::cout << "max_value: " << max_value << "\n";

    image->rgb = new unsigned char**[height];

    for (int i = 0; i < height; i++) {
        image->rgb[i] = new unsigned char*[width];
        for (int j = 0; j < width; j++) {
            image->rgb[i][j] = new unsigned char[3];
            for (int k = 0; k < 3; k++)
                image->rgb[i][j][k] = i_f.get();
        }
    }

    image->width = width;
    image->height = height;

    return image;
}

int is_same_color(unsigned char* rgb1, unsigned char* rgb2) {
    return ((rgb1[0] == rgb2[0])
            && (rgb1[1] == rgb2[1])
            && (rgb1[2] == rgb2[2]));
}

void print_vectors(const disjoint_set ds, int size) {
    std::cout << "Node #\n";
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(3) << i;
        if (i+1 < size)
            std::cout << "  ";
    }
    std::cout << "\n";

    std::cout << "Sets\n";
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(3) << ds.sets[i];
        if (i+1 < size)
            std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "Sizes\n";
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(3) << ds.sizes[i];
        if (i+1 < size)
            std::cout << ", ";
    }
    std::cout << "\n";

    std::cout << "Ranks\n";
    for (int i = 0; i < size; i++) {
        std::cout << std::setw(3) << ds.ranks[i];
        if (i+1 < size)
            std::cout << ", ";
    }
    std::cout << "\n";
}