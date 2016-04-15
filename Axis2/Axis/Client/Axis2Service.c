
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

#include <stdio.h>
#include <axiom.h>
#include <axis2_util.h>
#include <axiom_soap.h>
#include <axis2_client.h>

axiom_node_t *build_om_request(
    const axutil_env_t * env, const char *json);

const axis2_char_t *process_om_response(
    const axutil_env_t * env,
    axiom_node_t * node);

int
main(
    int argc,
    char **argv)
{
    const axutil_env_t *env = NULL;
    const axis2_char_t *address = NULL;
    axis2_endpoint_ref_t *endpoint_ref = NULL;
    axis2_options_t *options = NULL;
    const axis2_char_t *client_home = NULL;
    axis2_svc_client_t *svc_client = NULL;
    axiom_node_t *payload = NULL;
    axiom_node_t *ret_node = NULL;
    const char *json;
    
    env = axutil_env_create_all("Axis2Service_client.log", AXIS2_LOG_LEVEL_TRACE);

    options = axis2_options_create(env);

    address = "http://localhost:9090/axis2/services/Axis2Service";
    if (argc > 1)
      json = argv[1];
    else if (argc > 2)
        address = argv[1];
    if (axutil_strcmp(address, "-h") == 0)
    {
        printf("Usage : %s [endpoint_url]\n", argv[0]);
        printf("use -h for help\n");
        return 0;
    }
    printf("Using endpoint : %s\n", address);
    endpoint_ref = axis2_endpoint_ref_create(env, address);
    axis2_options_set_to(options, env, endpoint_ref);

    client_home = AXIS2_GETENV("AXIS2C_HOME");
    if (!client_home && !strcmp(client_home, ""))
        client_home = "../..";

    svc_client = axis2_svc_client_create(env, client_home);
    if (!svc_client)
    {
        printf("Error creating service client\n");
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI,
                        "Stub invoke FAILED: Error code:" " %d :: %s",
                        env->error->error_number,
                        AXIS2_ERROR_GET_MESSAGE(env->error));
        return -1;
    }

    axis2_svc_client_set_options(svc_client, env, options);

    payload = build_om_request(env, json);

    ret_node = axis2_svc_client_send_receive(svc_client, env, payload);

    if (ret_node)
    {
        const axis2_char_t *response = process_om_response(env, ret_node);
        if (response)
            printf("\nReceived : \"%s\" from service\n", response);

        axiom_node_free_tree(ret_node, env);
        ret_node = NULL;
    }
    else
    {
        AXIS2_LOG_ERROR(env->log, AXIS2_LOG_SI,
                        "Stub invoke FAILED: Error code:" " %d :: %s",
                        env->error->error_number,
                        AXIS2_ERROR_GET_MESSAGE(env->error));
        printf("Axis2Service client invoke FAILED!\n");
    }

    if (svc_client)
    {
        axis2_svc_client_free(svc_client, env);
        svc_client = NULL;
    }

    if (env)
    {
        axutil_env_free((axutil_env_t *) env);
        env = NULL;
    }

    return 0;
}

axiom_node_t *
build_om_request(
    const axutil_env_t * env,
    const char *json)
{
    axiom_node_t *request_om_node = NULL;
    axiom_element_t *request_om_ele = NULL;

    request_om_ele = axiom_element_create(env, NULL, "json", NULL, &request_om_node);
    axiom_element_set_text(request_om_ele, env, json, request_om_node);

    return request_om_node;
}

const axis2_char_t *
process_om_response(
    const axutil_env_t * env,
    axiom_node_t * node)
{
    axiom_node_t *service_response_node = NULL;
    axiom_node_t *return_node = NULL;

    if (node)
    {
        service_response_node = axiom_node_get_first_child(node, env);
        if (service_response_node &&
            axiom_node_get_node_type(service_response_node, env) == AXIOM_TEXT)
        {
            axiom_text_t *response =
                (axiom_text_t *)
                axiom_node_get_data_element(service_response_node, env);
            if (response && axiom_text_get_value(response, env))
            {
                return axiom_text_get_value(response, env);
            }
        }
    }
    return NULL;
}
