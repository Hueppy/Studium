package com.wba.projectportal.webservice;

import com.wba.projectportal.model.Project;
import com.wba.projectportal.model.Scope;

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

@Path("/scope")
public class ScopeResource {
    @PersistenceContext(unitName = "default")
    private EntityManager em;

    @Resource
    private UserTransaction utx;

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response all() {
        List<Scope> scopes = em.createNamedQuery("Scope.all", Scope.class).getResultList();
        Response.ResponseBuilder rb = Response.ok();
        rb.entity(scopes);

        return rb.build();
    }

    @GET
    @Path("{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response single(@PathParam("id") int id) {
        Response.ResponseBuilder rb;

        try {
            TypedQuery<Scope> query = em.createNamedQuery("Scope.single", Scope.class);
            query.setParameter("id", id);
            Scope p = query.getSingleResult();

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
    public Response create(Scope scope) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            this.em.persist(scope);
            this.utx.commit();
            rb = Response.created(URI.create(Integer.toString(scope.getId())));
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e);
        }

        return rb.build();
    }

    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response update(Scope scope) {
        Response.ResponseBuilder rb;

        try {
            this.utx.begin();
            em.merge(scope);
            this.utx.commit();

            rb = Response.ok();
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e.toString());
        }

        return rb.build();
    }
}
