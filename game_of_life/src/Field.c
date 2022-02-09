#include "../include/Field.h"

#include <string.h>

Field* Field_init(const char* dir) {
    Field* field = malloc(sizeof(Field));
    field->picture = BMP_init();
    field->dir = malloc(strlen(dir) + 1);
    field->dir[strlen(dir)] = '\0';
    field->dir = strcpy(field->dir, dir);
    field->frame = 0;
    return field;
}

char* int_to_str(int n) {
    int save = n;
    int len = 0;
    while (save /= 10) {
        len++;
    }
    len++;
    char* out = malloc(len + 1);
    out[len] = 0;
    for (int i = len - 1; i >= 0; i--) {
        out[i] = n % 10 + '0';
        n /= 10;
    }
    return out;
}

char* generate_framename(Field* self) {
    char* number = int_to_str(self->frame++);
    // char* number = int_to_str(self->frame);
    char* ext = ".bmp";
    int len = strlen(self->dir) + strlen(number) + strlen(ext);
    char* out = malloc(len + 1);
    out[0] = 0;
    out[len] = 0;
    strcat(out, self->dir);
    strcat(out, number);
    strcat(out, ext);
    free(number);
    // printf("%s\n", out);
    return out;
}

void Field_write(Field* self) {
    char* framename = generate_framename(self);
    BMP_write(self->picture, framename);
    free(framename);
}

void Field_generate_from_file(Field* self, char* filename) {
    BMP_read(self->picture, filename);
    Field_write(self);

    if (self->picture->info_header->BitCount == 24) {
        BMP_from24to8(self->picture);
        Field_write(self);
    }

    if (self->picture->info_header->BitCount == 8) {
        BMP_from8to1(self->picture);
        Field_write(self);
    }
}

uchar Field_get_cell(Field* self, uint x, uint y) {
    if (x == (uint)-1 || x == self->picture->info_header->Height) {
        return 0;
    }
    if (y == (uint)-1 || y == self->picture->info_header->Width) {
        return 0;
    }
    if (self->picture->info_header->Height < x) {
        printf("#ERROR trying to reach cell that doesn't exist\n");
        printf("Height = %d, x = %d\n", self->picture->info_header->Height, x);
        exit(1);
    }
    if (self->picture->info_header->Width < y) {
        printf("#ERROR trying to reach cell that doesn't exist\n");
        printf("Width = %d, y = %d\n", self->picture->info_header->Width, y);
        exit(1);
    }

    return (self->picture->image[x][y / 8] & (1 << (7 - y % 8))) != 0;
}

void Field_put_cell(Field* self, uint x, uint y, uchar value) {
    if (self->picture->info_header->Height < x) {
        printf("#ERROR trying to reach cell that doesn't exist\n");
        printf("Height = %d, x = %d\n", self->picture->info_header->Height, x);
        exit(1);
    }
    if (self->picture->info_header->Width < y) {
        printf("#ERROR trying to reach cell that doesn't exist\n");
        printf("Width = %d, y = %d\n", self->picture->info_header->Width, y);
        exit(1);
    }

    if (Field_get_cell(self, x, y)) {
        if (!value) {
            self->picture->image[x][y / 8] -= (1 << (7 - y % 8));
        }
    } else if (value) {
        self->picture->image[x][y / 8] += (1 << (7 - y % 8));
    }
}

uchar Image_get_cell(uchar** image, uint x, uint y) {
    return (image[x][y / 8] & (1 << (7 - y % 8))) != 0;
}

void Image_put_cell(uchar** image, uint x, uint y) {
    image[x][y / 8] |= (1 << (7 - y % 8));
}

void Field_print(Field* self) {
    printf("Field:\n");
    for (uint i = 0; i < self->picture->info_header->Height; i++) {
        for (uint j = 0; j < self->picture->info_header->Width; j++) {
            printf("%d ", Field_get_cell(self, i, j));
        }
        printf("\n");
    }
}

void Field_increase_and_copy(Field* self, uchar up, uchar down, uchar left, uchar right) {
    if (up + down + right + left == 0) {
        return;
    }

    self->picture->info_header->Width += left + right;
    self->picture->info_header->Height += up + down;
    uint old_width_bytes = self->picture->info_header->WidthBytes;
    BMP_calc_dimensions(self->picture);

    self->picture->file_header->FileSize -= self->picture->info_header->ImageSize;
    self->picture->info_header->ImageSize = self->picture->info_header->WidthBytes *
                                            self->picture->info_header->Height;
    self->picture->file_header->FileSize += self->picture->info_header->ImageSize;

    uchar** new_image = (uchar**)malloc(self->picture->info_header->Height * sizeof(uchar*));
    for (uint i = 0; i < self->picture->info_header->Height; i++) {
        new_image[i] = (uchar*)malloc((self->picture->info_header->WidthBytes + 1) * sizeof(uchar));
        for (uint j = 0; j <= self->picture->info_header->WidthBytes; j++) {
            new_image[i][j] = '\0';
        }
    }

    for (uint i = up; i < self->picture->info_header->Height - down; i++) {
        uint carry = 0;
        for (uint j = 0; j < old_width_bytes; j++) {
            if (left) {
                new_image[i][j] = self->picture->image[i - up][j] >> 1;
                new_image[i][j] += carry << 7;
                carry = self->picture->image[i - up][j] & 1;
            } else {
                new_image[i][j] = self->picture->image[i - up][j];
            }
        }
        if (old_width_bytes < self->picture->info_header->WidthBytes) {
            new_image[i][old_width_bytes + 1] = carry << 7;
        }
    }

    for (uint i = 0; i < self->picture->info_header->Height - up - down; i++) {
        free(self->picture->image[i]);
    }
    free(self->picture->image);
    self->picture->image = new_image;
}

void Field_adjust_sides(Field* self) {
    uchar up = 0, down = 0, right = 0, left = 0;
    for (uint i = 1; i < self->picture->info_header->Width - 1; i++) {
        if (!up) {
            up = Field_get_cell(self, 0, i - 1) &&
                 Field_get_cell(self, 0, i) &&
                 Field_get_cell(self, 0, i + 1);
        }
        if (!down) {
            down = Field_get_cell(self, self->picture->info_header->Height - 1, i - 1) &&
                   Field_get_cell(self, self->picture->info_header->Height - 1, i) &&
                   Field_get_cell(self, self->picture->info_header->Height - 1, i + 1);
        }
    }

    for (uint i = 1; i < self->picture->info_header->Height - 1; i++) {
        if (!left) {
            left = Field_get_cell(self, i - 1, 0) &&
                   Field_get_cell(self, i, 0) &&
                   Field_get_cell(self, i + 1, 0);
        }
        if (!right) {
            right = Field_get_cell(self, i - 1, self->picture->info_header->Width - 1) &&
                    Field_get_cell(self, i, self->picture->info_header->Width - 1) &&
                    Field_get_cell(self, i + 1, self->picture->info_header->Width - 1);
        }
    }

    // printf("up = %d\ndown = %d\nright = %d\nleft = %d\n", up, down, right, left);
    Field_increase_and_copy(self, up, down, left, right);
}

uint count_cells(uint cells) {
    int out = 0;
    for (int i = 0; i < 9; i++) {
        out += cells & 1;
        cells >>= 1;
    }
    return out;
}

uint Field_get_three_cells(Field* self, uint x, uint y) {
    // int out = 0;
    // for (int i = -1; i <= 1; i++) {        
    //     out += Field_get_cell(self, x + i, y);
    // }
    return Field_get_cell(self, x-1, y) + Field_get_cell(self, x, y) + Field_get_cell(self, x+1, y);
}

void Field_make_turn(Field* self) {
    Field_adjust_sides(self);

    uchar** new_image = (uchar**)malloc(self->picture->info_header->Height * sizeof(uchar*));
    for (uint i = 0; i < self->picture->info_header->Height; i++) {
        new_image[i] = (uchar*)malloc((self->picture->info_header->WidthBytes + 1) * sizeof(uchar));
        for (uint j = 0; j <= self->picture->info_header->WidthBytes; j++) {
            new_image[i][j] = '\0';
        }
    }
    for (uint i = 0; i < self->picture->info_header->Height; i++) {
        uint prev = 0;
        uint cur = Field_get_three_cells(self, i, 0);      
        uint next = 0;
        for (uint j = 0; j < self->picture->info_header->Width; j++) {            
            next = Field_get_three_cells(self, i, j + 1);
            uint count = prev+cur+next;
            // printf("%d, %d\n", i, j);
            if (count == 3 || (count == 4 && Field_get_cell(self, i, j))) {
                Image_put_cell(new_image, i, j);
            }
            prev = cur;
            cur = next;
        }
    }

    BMP_image_free(self->picture);
    self->picture->image = new_image;
    Field_write(self);
}

void Field_free(Field* self) {
    BMP_free(self->picture);
    free(self->dir);
    free(self);
}