#ifndef UTILS_H
    #define UTILS_H
    #include <time.h>
    #include <stdio.h>
    #include <stdarg.h>
    #include <assert.h>
    #include <stdlib.h>
    #include <math.h>
    #include <stdarg.h>
    #include <stdint.h>
    #include <stddef.h>
    #include <string.h>
    #include <ctype.h>

    typedef uint8_t  u08;
    typedef uint16_t u16;
    typedef uint32_t u32; 
    typedef uint64_t u64;

    typedef int8_t  i08;
    typedef int16_t i16; 
    typedef int32_t i32;
    typedef int64_t i64;

    typedef float f32;
    typedef double f64;

    #define i08_min -128
    #define i16_min -32768
    #define i32_min -2147483647 - 1
    #define i64_min -9223372036854775807LL - 1

    #define i08_max  127 
    #define i16_max  32767
    #define i32_max  2147483647
    #define i64_max  9223372036854775807LL

    #define u08_max  0xff
    #define u16_max  0xffff
    #define u32_max  0xffffffff
    #define u64_max  0xffffffffffffffffULL 

    typedef struct {
        char * content;
        const char * path;
        u32 len;
    } file_info_t;

    i08 file_exists(const char * path);
    file_info_t txt_file_query(const char * path);
    i08 txt_file_write(const char * content, const char * path, const size_t len); 

    typedef struct {
        const char * id;
        u64 hash;
        void * val;
    } ht_item_t;

    typedef struct {
        ht_item_t ** data;
        u32 len;
        u32 capacity;
    } ht_t; 

    ht_t ht_create(const u32 capacity);
    u64 ht_insert(ht_t * ht, const char * id, void * data); 
    void * ht_get(const ht_t * ht, const char * id);
    u64 ht_rm_data(ht_t * ht, const char * id);
    void ht_rm(ht_t * ht);

    typedef struct {
        void ** data;
        u32 capacity;
        u32 len;
    } list_t;

    list_t list_create(const u32 capacity);
    void list_insert(list_t * list, void * data);
    i32 list_get_idx_of(const list_t list, void * data);
    void list_rm_at(list_t * list, u32 idx);
    void list_rm_data(list_t * list, void * data);
    void list_rm(list_t * list);

    #define list_get_at(list, index) \
        list.data[index]

    #define list_get_data(list, data) \
        get_at_list(list, get_list_idx(&list, (void *)data))


    typedef enum {
        LOG_DBG,
        LOG_SUCCESS,
        LOG_WARN,
        LOG_ERR,
        LOG_LEVEL_LEN
    } LOG_LEVEL;

    void logger_log(LOG_LEVEL level, const char * fmt, ...);

    #define pi 3.141592653589793238462643383279
    #define deg_to_rad(deg) deg * (pi / 180)
    #define rad_to_deg(rad) rad * (180 / pi)
    #define sq(e) (e) * (e)

    f32 dist2D(f32 x1, f32 y1, f32 x2, f32 y2);
    f32 dir2D(f32 x1, f32 y1, f32 x2, f32 y2);
    f32 ilerp(f32 start, f32 stop, f32 amt);
    i64 randnum_gen(i64 lower, i64 upper);

    // Note projection functions 
    // project v1 onto v2

    typedef struct {
        f64 x;
        f64 y;
    } v2_t;

    #define mk_v2_zero() (v2_t)  { 0.0f, 0.0f }
    #define mk_v2_one () (v2_t)  { 1.0f, 1.0f }
    #define mk_v2(_x, _y) (v2_t) { (_x), (_y) }

    v2_t v2_add(v2_t v1, v2_t v2);
    v2_t v2_sub(v2_t v1, v2_t v2);
    v2_t v2_lerp(v2_t v1, v2_t v2, f32 amt);
    void v2_scale(v2_t * v, f32 scalar);
    void v2_normalize(v2_t * v);
    void v2_limit(v2_t * v, f32 scalar);
    void v2_rotate(v2_t * v, f32 theta);
    void v2_mag_set(v2_t * v, f32 scalar);
    void v2_negate(v2_t * v);

    f32 v2_mag(v2_t v);
    f32 v2_angle(v2_t v);
    f32 v2_dot_prod(v2_t v1, v2_t v2);
    f32 v2_dist_between(v2_t v1, v2_t v2);
    f32 v2_angle_between(v2_t v1, v2_t v2);
    v2_t v2_projection(v2_t v1, v2_t v2);


    typedef struct {
        f32 elements[3];
        union {
            f32 x, r;
        };
        union {
            f32 y, g;
        };
        union {
            f32 z, b;
        };
    } v3_t;

    #define mk_v3_zero()      (v3_t) { 0.0f, 0.0f, 0.0f }
    #define mk_v3_one ()      (v3_t) { 1.0f, 1.0f, 1.0f }
    #define mk_v3(_x, _y, _z) (v3_t) { (_x), (_y), (_z) }

    v3_t v3_add      (v3_t v1, v3_t v2);
    v3_t v3_sub      (v3_t v1, v3_t v2);
    v3_t v3_lerp     (v3_t v1, v3_t v2, f32 amt);
    void v3_limit    (v3_t * v, f32 scalar);
    void v3_scale    (v3_t * v, f32 scalar);
    void v3_normalize(v3_t * v);
    void v3_mag_set  (v3_t * v, f32 scalar);
    void v3_negate   (v3_t * v);

    f32   v3_mag          (v3_t v);
    f32   v3_dot_prod     (v3_t v1, v3_t v2);
    v3_t  v3_cross_prod   (v3_t v1, v3_t v2);
    f32   v3_dist_between (v3_t v1, v3_t v2); 
    f32   v3_angle_between(v3_t v1, v3_t v2);
    v3_t  v3_projection   (v3_t v1, v3_t v2);

    typedef struct {
        f32 elements[4];
        union {
            f32 x, r;
        };
        union {
            f32 y, g;
        };
        union {
            f32 z, b;
        };
        union {
            f32 w, a;
        }; 
    } v4_t;



    #define mk_v4_zero()          (v4_t) { 0.0f, 0.0f, 0.0f, 0.0f }
    #define mk_v4_one ()          (v4_t) { 1.0f, 1.0f, 1.0f, 1.0f }
    #define mk_v4(_x, _y, _z, _w) (v4_t) { (_x), (_y), (_z), (_w) }


    v4_t v4_add      (v4_t v1, v4_t v2);
    v4_t v4_sub      (v4_t v1, v4_t v2);
    v4_t v4_lerp     (v4_t v1, v4_t v2, f32 amt);
    void v4_limit    (v4_t * v, f32 scalar);
    void v4_scale    (v4_t * v, f32 scalar);
    void v4_normalize(v4_t * v);
    void v4_mag_set  (v4_t * v, f32 scalar);
    void v4_negate   (v4_t * v);

    f32  v4_mag         (v4_t v);
    f32  v4_dot_prod    (v4_t v1, v4_t v2);
    f32  v4_dist_between(v4_t v1, v4_t v2); 
    v4_t v4_projection  (v4_t v1, v4_t v2);


    v3_t v2_to_v3(const v2_t v);
    v4_t v3_to_v4(const v3_t v);
    v3_t v4_to_v3(const v4_t v);
    v2_t v3_to_v2(const v3_t v);

    typedef struct {
        f32 elems[4][4];
    } m4x4_t;

    m4x4_t mk_m4x4(f32 m00, f32 m01, f32 m02, f32 m03,
                   f32 m04, f32 m05, f32 m06, f32 m07,
                   f32 m08, f32 m09, f32 m10, f32 m11,
                   f32 m12, f32 m13, f32 m14, f32 m15);
    // Some of the code has been took from
    // https://github.com/MrFrenik/gunslinger/blob/v0.02-alpha/include/math/gs_math.h
    // https://github.com/arkanis/single-header-file-c-libs/blob/master/math_3d.h
    // learnopengl.com/Getting-started/Transformations
    m4x4_t mk_zero_m4x4    ();
    m4x4_t mk_identity_m4x4();
    m4x4_t mk_diag_m4x4    (f32 val);

    m4x4_t m4x4_add    (m4x4_t m1, m4x4_t m2); 
    m4x4_t m4x4_sub    (m4x4_t m1, m4x4_t m2); 
    m4x4_t m4x4_mult   (m4x4_t m1, m4x4_t m2); 
    m4x4_t m4x4_mult_n (u32 m4x4_count, ...);
    v3_t   m4x4_mult_v3(m4x4_t m, v3_t v);
    v4_t   m4x4_mult_v4(m4x4_t m, v4_t v);

    m4x4_t m4x4_scale_by_v3    (m4x4_t mat, const v3_t vector);
    m4x4_t m4x4_translate_by_v3(m4x4_t mat, const v3_t vector);
    m4x4_t m4x4_rotate_by_v3   (f32 degrees, v3_t axis);

    m4x4_t m4x4_orthographic_projection(f32 l, f32 r, f32 b, 
                                        f32 t, f32 n, f32 f);
    
    m4x4_t m4x4_perspective_projection(f32 fov, f32 asp_ratio, f32 n, f32 f);
    m4x4_t m4x4_lookat                (v3_t pos, v3_t target, v3_t up);

    // Add:
    //  m3x3_t 
        //  lookat
    //  quternions
        //  
    // objects
    // rays

    typedef struct {
        char * name;
        f64 elapsed;
        clock_t start;
        clock_t end;
    } prof_t;

    void prof_start(prof_t * profiler, char * name);
    void prof_end(prof_t * profiler);


    // maybe custom string functions
    char * i32_to_str(i32 num);
    char * f64_to_str(f64 num);
    i32 str_to_i32(char * string);


    typedef struct {
        file_info_t file;
        u64 len;
        u32 max_elems_in_list;
        u64 max_str_byte_size;
        char ** data;
        ht_t table;
    } config_file_t;


    config_file_t parse_config_file(const char * filepath);
    void ** config_file_get(config_file_t * file, char * key);

    // Extra maths


#endif