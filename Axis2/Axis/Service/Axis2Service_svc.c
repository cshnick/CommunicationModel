
/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <axis2_svc_skeleton.h>
#include <axutil_log_default.h>
#include <axutil_error_default.h>
#include <axutil_array_list.h>
#include <axiom_text.h>
#include <axiom_node.h>
#include <axiom_element.h>
#include <stdio.h>

#include <jansson.h>

axiom_node_t *axis2_process(
    const axutil_env_t * env,
    axiom_node_t * node);

int AXIS2_CALL clear(
    axis2_svc_skeleton_t * svc_skeleton,
    const axutil_env_t * env);

axiom_node_t *AXIS2_CALL invoke(
    axis2_svc_skeleton_t * svc_skeleton,
    const axutil_env_t * env,
    axiom_node_t * node,
    axis2_msg_ctx_t * msg_ctx);

int AXIS2_CALL init(
    axis2_svc_skeleton_t * svc_skeleton,
    const axutil_env_t * env);

axiom_node_t *AXIS2_CALL on_fault(
    axis2_svc_skeleton_t * svc_skeli,
    const axutil_env_t * env,
    axiom_node_t * node);

axiom_node_t *build_response(
    const axutil_env_t * env,
    axis2_char_t * greeting);

axiom_node_t *
axis2_process(
    const axutil_env_t * env,
    axiom_node_t * node)
{
    axiom_node_t *client_node = NULL;
    axiom_node_t *return_node = NULL;

    AXIS2_ENV_CHECK(env, NULL);

    if (node)
    {
        client_node = axiom_node_get_first_child(node, env);
        if (client_node &&
            axiom_node_get_node_type(client_node, env) == AXIOM_TEXT)
        {
            axiom_text_t *received =
                (axiom_text_t *)
                axiom_node_get_data_element(client_node, env);
            if (received && axiom_text_get_value(received, env))
            {
                const axis2_char_t *received_str =
                    axiom_text_get_value(received, env);
                printf("Received from client \"%s\" \n", received_str);
		
		//Parse JSON
		json_t *receivedJson = json_string(received_str);
		
		if (receivedJson)
		  return_node = build_response(env, "Processed SUCCEEDED!");
		else
		  return_node = build_response(env, "Processed FAILED!");
            }
        }
    }
    else
    {
        AXIS2_ERROR_SET(env->error,
                        AXIS2_ERROR_SVC_SKEL_INVALID_XML_FORMAT_IN_REQUEST,
                        AXIS2_FAILURE);
        printf("ERROR: invalid XML in request\n");
        return_node = build_response(env, "Client! Who are you?");
    }

    return return_node;
}

axiom_node_t *
build_response(
    const axutil_env_t * env,
    axis2_char_t * message)
{
    axiom_node_t *om_node = NULL;
    axiom_element_t *om_ele = NULL;

    om_ele =
        axiom_element_create(env, NULL, "greetResponse", NULL,
                             &om_node);

    axiom_element_set_text(om_ele, env, message, om_node);

    return om_node;
}

static const axis2_svc_skeleton_ops_t svc_skeleton_ops_var = {
    init,
    invoke,
    on_fault,
    clear
};

axis2_svc_skeleton_t *
axis2_create(
    const axutil_env_t * env)
{
    axis2_svc_skeleton_t *svc_skeleton = NULL;
    svc_skeleton = AXIS2_MALLOC(env->allocator, sizeof(axis2_svc_skeleton_t));

    svc_skeleton->ops = &svc_skeleton_ops_var;

    svc_skeleton->func_array = NULL;

    return svc_skeleton;
}

int AXIS2_CALL
init(
    axis2_svc_skeleton_t * svc_skeleton,
    const axutil_env_t * env)
{
    svc_skeleton->func_array = axutil_array_list_create(env, 0);
    axutil_array_list_add(svc_skeleton->func_array, env, "helloString");
    return AXIS2_SUCCESS;
}

axiom_node_t *AXIS2_CALL
invoke(
    axis2_svc_skeleton_t * svc_skeleton,
    const axutil_env_t * env,
    axiom_node_t * node,
    axis2_msg_ctx_t * msg_ctx)
{
    return axis2_process(env, node);
}

axiom_node_t *AXIS2_CALL
on_fault(
    axis2_svc_skeleton_t * svc_skeli,
    const axutil_env_t * env,
    axiom_node_t * node)
{
    axiom_node_t *error_node = NULL;
    axiom_node_t *text_node = NULL;
    axiom_element_t *error_ele = NULL;
    error_ele = axiom_element_create(env, node, "EchoServiceError", NULL,
                                     &error_node);
    axiom_element_set_text(error_ele, env, "Echo service failed ", text_node);
    return error_node;
}

int AXIS2_CALL
clear(
    axis2_svc_skeleton_t * svc_skeleton,
    const axutil_env_t * env)
{
    if (svc_skeleton->func_array)
    {
        axutil_array_list_free(svc_skeleton->func_array, env);
        svc_skeleton->func_array = NULL;
    }

    if (svc_skeleton)
    {
        AXIS2_FREE(env->allocator, svc_skeleton);
        svc_skeleton = NULL;
    }

    return AXIS2_SUCCESS;
}

AXIS2_EXPORT int
axis2_get_instance(
    axis2_svc_skeleton_t ** inst,
    const axutil_env_t * env)
{
    *inst = axis2_create(env);
    if (!(*inst))
    {
        return AXIS2_FAILURE;
    }

    return AXIS2_SUCCESS;
}

AXIS2_EXPORT int
axis2_remove_instance(
    axis2_svc_skeleton_t * inst,
    const axutil_env_t * env)
{
    axis2_status_t status = AXIS2_FAILURE;
    if (inst)
    {
        status = AXIS2_SVC_SKELETON_FREE(inst, env);
    }
    return status;
}
