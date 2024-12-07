/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 22:06:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/12/07 16:52:41 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# define OFFSET_NORMAL 1e-4
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

# ifndef DEBUG_TOOLS
#  define DEBUG_TOOLS 1
# endif

# include "libft.h"
# include "mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <float.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
}						t_image;

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

t_vector				get_direction_vector(t_vector from, t_vector to);
float					get_min_float(double *t, int size);
float					get_max_float(double *t, int size);
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

void					check_scene(t_scene *scene);
void					parse_ambient_light(t_scene *scene, char **instructions,
							size_t argc);
void					check_line(char **instructions, t_scene *scene, int fd);

void					split_and_assign_vector(t_objects *object, char *line,
							t_object_param type, t_scene *scene);
void					check_values(void *object, t_object_type type,
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
void					free_objects(t_objects *objects);

int						close_win(void *context, int exit_code);
int						close_win_handler(void *context);

void					render_scene(t_scene *scene);
void					print_array(char **array);

double					vector_length(t_vector vector);
t_vector				multiply_v_color(t_vector v1, t_vector v2);
float					dot_product(t_vector one, t_vector two);
float					get_angle_between(t_vector one, t_vector two);
t_vector				normalize_vector(t_vector vector);
void					print_vector(t_vector vector);

float					rad_to_deg(float rad);
float					deg_to_rad(float deg);

void					print_objects_parameters(t_scene *scene);

void					init_scene(t_scene *scene);
void					initialize_mlx(t_scene *scene);
int						key_hook(int keycode, t_scene *scene);
int						mouse_hook(int x, int y, t_scene *scene);
void					my_mlx_pixel_put(t_image *data, int x, int y,
							int color);

t_vector				subtract_v(t_vector one, t_vector two);
t_vector				divide_v(t_vector vector, float divider);
t_vector				multiply_v(t_vector vector, float multiplier);
t_vector				add_v(t_vector one, t_vector two);
t_vector				cross_product(t_vector one, t_vector two);

t_vector				rotate_on_x(t_vector vector);
t_vector				rotate_on_y(t_vector vector);
t_vector				rotate_on_z(t_vector vector);
t_vector				rotate_vector(float m[3][3], t_vector v);

bool					did_switch_signs_v(t_vector v1, t_vector v2);

int						rgb_to_int(int r, int g, int b);
int						color_to_int(t_color color);
int						vector_to_int(t_vector vector);
t_vector				color_to_vector(t_color color);
void					initialize_viewport(t_scene *scene);

// debug2.c
void					print_sphere_parameters(t_sphere *sphere);
void					print_plane_parameters(t_plane *plane);
void					print_light_parameters(t_lights *light);
void					print_cylinder_parameters(t_cylinder *cylinder);
void					print_camera_parameters(t_camera *camera);

// debug3.c
void					print_ambient_parameters(t_ambient *ambient);
void					print_objects_parameters(t_scene *scene);
void					show_depth(t_scene scene);

#endif
