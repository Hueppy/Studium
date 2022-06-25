package com.wba.projectportal.webservice;

import com.wba.projectportal.model.Artifact;
import com.wba.projectportal.model.Project;

import javax.annotation.Resource;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;
import javax.persistence.TypedQuery;
import javax.transaction.UserTransaction;
import javax.ws.rs.*;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import java.net.URI;
import java.time.Duration;
import java.time.temporal.ChronoUnit;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

@Path("/artifact")
public class ArtifactResource {
    @PersistenceContext(unitName = "default")
    private EntityManager em;

    @Resource
    private UserTransaction utx;

    @GET
    @Produces(MediaType.APPLICATION_JSON)
    public Response all() {
        List<Artifact> artifacts = em.createNamedQuery("Artifact.all", Artifact.class).getResultList();
        Response.ResponseBuilder rb = Response.ok();
        rb.entity(artifacts);

        return rb.build();
    }

    @GET
    @Path("{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response single(@PathParam("id") int id) {
        Response.ResponseBuilder rb;

        try {
            TypedQuery<Artifact> query = em.createNamedQuery("Artifact.single", Artifact.class);
            query.setParameter("id", id);
            Artifact a = query.getSingleResult();

            rb = Response.ok();
            rb.entity(a);
        } catch (Exception e) {
            rb = Response.status(Response.Status.NOT_FOUND);
        }

        return rb.build();
    }

    @POST
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response create(Artifact artifact) {
        Response.ResponseBuilder rb;
        try {
            this.utx.begin();
            this.em.persist(artifact);
            this.utx.commit();
            rb = Response.created(URI.create(Integer.toString(artifact.getId())));
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e.toString());
        }

        return rb.build();
    }

    @PUT
    @Consumes(MediaType.APPLICATION_JSON)
    @Produces(MediaType.APPLICATION_JSON)
    public Response update(Artifact artifact) {
        Response.ResponseBuilder rb;
        try {
            this.utx.begin();
            em.merge(artifact);
            this.utx.commit();

            rb = Response.ok();
        } catch (Exception e) {
            rb = Response.serverError();
            rb.entity(e.toString());
        }

        return rb.build();
    }
}
