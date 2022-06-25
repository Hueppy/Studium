package com.wba.projectportal.webservice;

import com.wba.projectportal.model.Project;
import com.wba.projectportal.model.ProjectScope;

import javax.annotation.Resource;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import javax.transaction.UserTransaction;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.net.URI;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

@Path("/projectscope")
public class ProjectScopeResource {
    @PersistenceContext(unitName = "default")
    private EntityManager em;

    @Resource
    private UserTransaction utx;

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response all() {
        List<ProjectScope> projectScopes = em.createNamedQuery("ProjectScope.all", ProjectScope.class).getResultList();
        Response.ResponseBuilder rb = Response.ok();
        rb.entity(projectScopes);

        return rb.build();
    }

    @GET
    @Path("{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response single(@PathParam("id") int id) {
        Response.ResponseBuilder rb;

        try {
            TypedQuery<ProjectScope> query = em.createNamedQuery("ProjectScope.single", ProjectScope.class);
            query.setParameter("id", id);
            ProjectScope p = query.getSingleResult();

            rb = Response.ok();
            rb.entity(p);
        } catch (Exception e) {
            rb = Response.status(Response.Status.NOT_FOUND);
        }

        return rb.build();
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response create(ProjectScope projectScope) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            this.em.persist(projectScope);
            this.utx.commit();
            rb = Response.created(URI.create(Integer.toString(projectScope.getId())));
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e);
        }

        return rb.build();
    }
}
