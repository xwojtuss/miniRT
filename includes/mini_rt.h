/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:06:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2025/01/28 12:54:38 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# define OFFSET_NORMAL 1e-3
# define ROTATE_DEGREE 5
# define FOV_OFFSET 5
# define MOVE_STEP 0.5
# define MOUSE_SENSITIVITY 0.5

# define PI 3.14159265358979323846

# define NOT_SET -42

# define KEY_CLOSE_WINDOW 17
# define KEY_ESC 65307

# define WIN_HEIGHT_DEFAULT 1080
# define WIN_WIDTH_DEFAULT 1920

# define FLOAT_PITCH_LIMIT 0.98

# define DEFAULT_BACKGROUND_COLOR 0x000000

# ifndef DEBUG_TOOLS
#  define DEBUG_TOOLS 0
# endif

# ifndef DEBUG_INTER
#  define DEBUG_INTER 0
# endif

# define INTER_COLOR 0xff0000
# define INTER_WIDTH 10

# include "float.h"
# include "libft.h"
# include "mlx.h"
# include "vectors.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_constants
{
	float				ambient;
	float				diffuse;
	float				specular;
	float				shininess;
}						t_constants;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

typedef struct t_texture
{
	char				*name;
	t_image				img;
	int					width;
	int					height;
}						t_texture;

typedef enum e_object_param
{
	POSITION,
	ORIENTATION,
	DIAMETER,
	HEIGHT,
	COLOR,
	BRIGHTNESS,
	FOV
}						t_object_param;

typedef enum e_object_type
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
	CAMERA,
	LIGHT,
	AMBIENT,
	INTER,
	LINE
}						t_object_type;

typedef struct s_ray
{
	t_vector			origin;
	t_vector			direction;
}						t_ray;

typedef struct s_lights
{
	t_vector			position;
	float				brightness;
	t_color				color;
	struct s_lights		*next;
}						t_lights;

typedef struct s_ambient
{
	float				brightness;
	t_color				color;
}						t_ambient;

typedef struct s_objects
{
	void				*object;
	t_object_type		type;
	t_constants			constants;
	t_texture			*texture;
	t_texture			*bump;
	struct s_objects	*next;
}						t_objects;

typedef struct s_camera
{
	t_vector			position;
	t_vector			orientation;
	t_vector			right;
	t_vector			up;
	float				fov;
}						t_camera;

typedef struct s_sphere
{
	t_vector			position;
	float				diam;
	t_color				color;
}						t_sphere;

typedef struct s_plane
{
	t_vector			position;
	t_vector			orientation;
	float				diam;
	t_color				color;
}						t_plane;

typedef struct s_cylinder
{
	t_vector			position;
	t_vector			orientation;
	float				diam;
	float				height;
	t_color				color;
}						t_cylinder;

typedef struct s_cone
{
	t_vector			position;
	t_vector			orientation;
	float				diam;
	float				height;
	t_color				color;
}						t_cone;

typedef struct s_line
{
	t_vector			position;
	t_vector			orientation;
	t_color				color;
	float				length;
}						t_line;

typedef struct s_scene
{
	void				*mlx;
	void				*win;
	int					win_height;
	int					win_width;
	double				viewport_width;
	double				viewport_height;
	int					image_width;
	int					image_height;
	char				*file;
	t_objects			*selected;
	t_vector			viewport_grid_vector_x;
	t_vector			viewport_grid_vector_y;
	t_vector			viewport_top_left;
	t_image				img;
	t_objects			*objects;
	t_lights			*light;
	t_ambient			*ambient;
	t_camera			*camera;
}						t_scene;

//	SRCS
//		DATA
//			CHECK_SCENE.C

void					check_scene(t_scene *scene);
void					check_line(char **instructions, t_scene *scene, int fd);

//			ERRORS.C

void					err(char *message);
void					err_free(char *message, t_scene *scene);
void					err_free_array(char *message, t_scene *scene,
							char **array);

void					err_free_arrays(char *message, t_scene *scene,
							char **array, char **array2);

//			FREE.C

void					free_scene(t_scene *scene);
void					free_array(char **array);

//			INITIALIZE.C

void					initialize_viewport(t_scene *scene);
void					init_scene(t_scene *scene);

//			PARSE.C

void					parse_new_object(t_scene *scene, char **line,
							size_t argc, t_object_type type);
int						parse_line(t_scene *scene, int fd);

//		DEBUG
//			DEBUG.C

void					print_vector(t_vector vector);
void					print_array(char **array);
bool					check_debug_tools(int keycode, t_scene *scene);

//			DEBUG2.C

void					print_sphere_parameters(t_sphere *sphere);
void					print_plane_parameters(t_plane *plane);
void					print_cylinder_parameters(t_cylinder *cylinder);
void					print_cone_parameters(t_cone *cone);
void					print_camera_parameters(t_camera *camera);
void					print_line_parameters(t_line *line);

//			DEBUG3.C

void					print_color(t_color color);
void					print_light_parameters(t_lights *light);
void					print_ambient_parameters(t_ambient *ambient);
void					print_object_parameters(t_objects *object);
void					print_objects_parameters(t_scene *scene);

//			DEBUG4.C

t_objects				*debug_intersect(void);

//		MATH
//			in vectors.h

//		MLX
//			MLX_HOOKS.C

int						key_hook(int keycode, t_scene *scene);
int						mouse_click_handler(int button, int x, int y,
							t_scene *scene);
int						close_win_handler(void *context);

//			MLX_INIT.C

void					open_textures(t_scene *scene);
void					initialize_mlx(t_scene *scene);

//			MLX_MISC.C

void					my_mlx_pixel_put(t_image *data, int x, int y,
							int color);
int						close_win(void *context, int exit_code);

//			TEXTURES.C

t_texture				*copy_texture(t_texture *reference);
unsigned int			get_pixel_color(t_image image, int x, int y);
void					assign_phong(t_objects *new, char **line, size_t start);
t_texture				*new_texture(char *name);

//		OBJECTS
//			AMBIENT.C

void					parse_ambient_light(t_scene *scene, char **instructions,
							size_t argc);

//			CAMERA.C

void					parse_camera(t_scene *scene, char **line, size_t argc);

//			CONE.C

void					check_cone_values(t_cone *cone, t_scene *scene,
							char **line);
void					assign_cone_values(void *object, char **temp,
							t_object_param type);
t_cone					*new_cone(t_scene *scene, t_objects *new, char **line,
							size_t argc);

//			CYLINDER.C

void					check_cylinder_values(t_cylinder *cylinder,
							t_scene *scene, char **line);
void					assign_cylinder_values(void *object, char **temp,
							t_object_param type);
t_cylinder				*new_cylinder(t_scene *scene, t_objects *new,
							char **line, size_t argc);

//			DIVIDE.C

void					add_base(t_scene *scene, t_objects *reference);
void					add_cap(t_scene *scene, t_objects *reference,
							bool is_top);
void					add_caps(t_scene *scene, char *type);

//			LIGHT.C

void					parse_light(t_scene *scene, char **instructions,
							size_t argc);

//			LINE.C

t_line					*new_line(t_scene *scene, t_objects *new, char **line,
							size_t argc);
void					assign_line_values(void *object, char **temp,
							t_object_param type);
void					check_line_values(t_line *o_line, t_scene *scene,
							char **line);

//			MISC.C

t_objects				*get_last_object(t_objects *objects);

//			PLANE.C

void					check_plane_values(t_plane *plane, t_scene *scene,
							char **line);
void					assign_plane_values(void *object, char **temp,
							t_object_param type);
t_plane					*new_plane(t_scene *scene, t_objects *new, char **line,
							size_t argc);

//			SPHERE.C

void					check_sphere_values(t_sphere *sphere, t_scene *scene,
							char **line);
void					assign_sphere_values(void *object, char **temp,
							t_object_param type);
t_sphere				*new_sphere(t_scene *scene, t_objects *new, char **line,
							size_t argc);

//		RAYTRACING
//			CHECK_INTERSECTIONS.C

bool					is_intersect_ray_cylinder(t_ray ray,
							t_cylinder *cylinder, double *prev_t);
bool					is_intersect_plane(t_ray ray, t_plane *plane,
							double *prev_t);
bool					is_intersect_sphere(t_ray ray, t_sphere *sphere,
							double *prev_t);
bool					is_intersect_cone(t_ray ray, t_cone *cone,
							double *prev_t);
bool					is_intersect_line(t_ray ray, t_line *line,
							double *prev_t);

//			CONSTANTS.C

void					assign_default_phong(t_objects *object);

//			FIND_T.C

void					retrieve_t(double a, double b, double disc,
							double *ts[2]);
void					get_t_sphere(t_sphere *sphere, t_ray ray, double *t1,
							double *t2);
void					get_t_cylinder(t_cylinder *cylinder, t_ray ray,
							double *t1, double *t2);
void					get_t_cone(t_cone *cone, t_ray ray, double *t1,
							double *t2);

//			INTERSECTION_MISC.C

t_vector				get_inter(t_ray ray, double t);
bool					check_side_cylinder(t_ray ray, t_cylinder *cylinder,
							double *t1, double *prev_t);
bool					check_side_cone(t_ray ray, t_cone *cone, double *t1,
							double *prev_t);
bool					is_inside_cylinder(t_vector ray_origin,
							t_cylinder cylinder);

//			NORMAL_VECTORS.C

t_vector				get_nv_sphere(t_vector inter, t_vector camera_pos,
							t_sphere *sphere);
t_vector				get_normal_vector_sphere(t_vector inter,
							t_vector center);
t_vector				get_nv_plane(t_ray ray, t_plane *plane);
t_vector				get_nv_cylinder(t_vector intersect,
							t_cylinder *cylinder, t_ray ray);
t_vector				get_nv_cone(t_vector intersect, t_cone *cone,
							t_ray ray);

//			PHONG.C
//				in phong_reflection.h
//			RENDER.C

t_objects				*get_closest_object(t_scene scene, t_ray ray,
							double *new_t);
void					render_scene(t_scene *scene);

//			UV_TRANSLATE.C
//				in phong_reflection.h

#endif
