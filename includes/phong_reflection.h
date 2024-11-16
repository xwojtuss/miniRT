#ifndef PHONG_REFLECTION_H
# define PHONG_REFLECTION_H

typedef struct s_raytrace_info
{
    t_vector    intersection_point;
    t_vector    normal_vector;
    t_vector    ray_direction;
    t_scene     scene;
}               t_raytrace_info;


# define SPECULAR_CONST
# define DIFFUSE_CONST
# define AMBIENT_CONST
# define SHININESS_CONST

#endif