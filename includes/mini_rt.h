/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:06:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/12/31 20:52:14 by wkornato         ###   ########.fr       */
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

# define WIN_HEIGHT_DEFAULT 600
# define WIN_WIDTH_DEFAULT 900

# define FLOAT_PITCH_LIMIT 0.98

# define DEFAULT_BACKGROUND_COLOR 0x000000

# ifndef DEBUG_TOOLS
#  define DEBUG_TOOLS 1
# endif

# include "float.h"
# include "libft.h"
# include "mlx.h"
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
	AMBIENT
}						t_object_type;

typedef struct s_color
{
	int					r;
	int					g;
	int					b;
}						t_color;

typedef struct s_vector
{
	float				x;
	float				y;
	float				z;
}						t_vector;

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
	t_vector			viewport_grid_vector_x;
	t_vector			viewport_grid_vector_y;
	t_vector			viewport_top_left;
	t_image				img;
	t_objects			*objects;
	t_lights			*light;
	t_ambient			*ambient;
	t_camera			*camera;
}						t_scene;

void					add_cap(t_scene *scene, t_objects *reference,
							bool is_top);
void					add_base(t_scene *scene, t_objects *reference);

void					assign_default_phong(t_objects *object,
							float ambient_const);
t_vector				int_color_to_vector(int color);
unsigned int			get_pixel_color(t_image image, int x, int y);

t_texture				*copy_texture(t_texture *reference);
t_texture				*new_texture(char *name);
void					assign_phong(t_objects *new, char **line, size_t start);

void					print_object_parameters(t_objects *object);
t_objects				*get_closest_object(t_scene scene, t_ray ray,
							double *new_t);
t_vector				get_inter(t_ray ray, double t);
void					retrieve_t(double a, double b, double disc,
							double *ts[2]);
double					is_intersect_cylinder_caps(t_ray ray,
							t_cylinder *cylinder, double *prev_t);
void					get_t_cylinder(t_cylinder *cylinder, t_ray ray,
							double *t1, double *t2);
t_vector				get_direction_vector(t_vector from, t_vector to);
void					assign_vector(t_vector *vector, float x, float y,
							float z);
void					assign_color(t_color *color, int r, int g, int b);

void					check_sphere_values(t_sphere *sphere, t_scene *scene,
							char **line);
void					assign_sphere_values(void *object, char **temp,
							t_object_param type);
t_sphere				*new_sphere(t_scene *scene, t_objects *new, char **line,
							size_t argc);

void					check_plane_values(t_plane *plane, t_scene *scene,
							char **line);
void					assign_plane_values(void *object, char **temp,
							t_object_param type);
t_plane					*new_plane(t_scene *scene, t_objects *new, char **line,
							size_t argc);

void					check_cylinder_values(t_cylinder *cylinder,
							t_scene *scene, char **line);
void					assign_cylinder_values(void *object, char **temp,
							t_object_param type);
t_cylinder				*new_cylinder(t_scene *scene, t_objects *new,
							char **line, size_t argc);

void					check_cone_values(t_cone *cone, t_scene *scene,
							char **line);
void					assign_cone_values(void *object, char **temp,
							t_object_param type);
t_cone					*new_cone(t_scene *scene, t_objects *new, char **line,
							size_t argc);
bool					check_side_cylinder(t_ray ray, t_cylinder *cylinder,
							double *t1, double *prev_t);
bool					check_side_cone(t_ray ray, t_cone *cone, double *t1,
							double *prev_t);
void	get_t_sphere(t_sphere *sphere, t_ray ray, double *t1, double *t2);
void	get_t_cone(t_cone *cone, t_ray ray, double *t1, double *t2);
void					check_scene(t_scene *scene);
void					parse_ambient_light(t_scene *scene, char **instructions,
							size_t argc);
void					check_line(char **instructions, t_scene *scene, int fd);
void					add_caps(t_scene *scene, char *type);
t_vector				clamp_vector(t_vector vector, int min, int max);
void					split_and_assign_vector(t_objects *object, char *line,
							t_object_param type, t_scene *scene);
void					check_values(t_objects *object, t_object_type type,
							t_scene *scene, char **line);
void					parse_new_object(t_scene *scene, char **line,
							size_t argc, t_object_type type);
int						parse_line(t_scene *scene, int fd);

void					parse_camera(t_scene *scene, char **line, size_t argc);
void					parse_light(t_scene *scene, char **instructions,
							size_t argc);
void					parse_ambient(t_scene *scene, char **instructions,
							size_t argc);

t_objects				*get_last_object(t_objects *objects);

void					err(char *error);
void					err_free(char *error, t_scene *scene);
void					err_free_array(char *error, t_scene *scene,
							char **array);
void					free_array(char **array);

void					free_scene(t_scene *scene);

int						close_win(void *context, int exit_code);
int						close_win_handler(void *context);

void					render_scene(t_scene *scene);
void					print_array(char **array);

double					vector_length(t_vector vector);
t_vector				multiply_v_color(t_vector v1, t_vector v2);
float					dot_product(t_vector one, t_vector two);
t_vector				normalize_vector(t_vector vector);
void					print_vector(t_vector vector);

float					deg_to_rad(float deg);

void					print_objects_parameters(t_scene *scene);

void					init_scene(t_scene *scene);
void					initialize_mlx(t_scene *scene);
int						key_hook(int keycode, t_scene *scene);
int						mouse_click_handler(int button, int x, int y,
							t_scene *scene);
void					my_mlx_pixel_put(t_image *data, int x, int y,
							int color);

t_vector				subtract_v(t_vector one, t_vector two);
t_vector				divide_v(t_vector vector, float divider);
t_vector				multiply_v(t_vector vector, float multiplier);
t_vector				add_v(t_vector one, t_vector two);
t_vector				cross_product(t_vector one, t_vector two);

int						rgb_to_int(int r, int g, int b);
int						color_to_int(t_color color);
int						vector_to_int(t_vector vector);
t_vector				color_to_vector(t_color color);
void					initialize_viewport(t_scene *scene);
t_vector				color_to_vector_cylinder(void *object);
t_vector				color_to_vector_sphere(void *object);
t_vector				color_to_vector_plane(void *object);
void					copy_vector(t_vector *dest, t_vector src);
void					copy_color(t_color *dest, t_color src);

bool					check_debug_tools(int keycode, t_scene *scene);

// debug2.c
void					print_sphere_parameters(t_sphere *sphere);
void					print_plane_parameters(t_plane *plane);
void					print_light_parameters(t_lights *light);
void					print_cylinder_parameters(t_cylinder *cylinder);
void					print_cone_parameters(t_cone *cone);
void					print_camera_parameters(t_camera *camera);

// debug3.c
void					print_ambient_parameters(t_ambient *ambient);
void					print_objects_parameters(t_scene *scene);

#endif
