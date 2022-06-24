using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Shared.Controllers;

[ApiController]
[Route("[controller]")]
public class ChronicleController : ControllerBase
{
    private PfotenFreundeContext context;

    public ChronicleController(PfotenFreundeContext context)
    {
        this.context = context;
    }

    /// <summary>
    /// Gets all chronicles
    /// </summary>
    [HttpGet]
    public IEnumerable<Chronicle> GetAll()
    {
        return this.context.Chronicles;
    }


    /// <summary>
    /// Gets information of the chronicle
    /// </summary>
    /// <response code="404">Chronicle not found</response>
    [HttpGet("{id}")]
    public async Task<ActionResult<Chronicle>> Get(int id)
    {
		var chronicle = await this.context.Chronicles.FindAsync(id);

		if (chronicle == null)
		{
			return NotFound();
		}

		return chronicle;
    }

    /// <summary>
    /// Gets all posts of the chronicle
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpGet("{id}/post")]
    public IEnumerable<Post> GetPosts(int id)
    {
		return this.context.Posts.Where(x => x.ChronicleId == id);
    }

    /// <summary>
    /// Adds a new post to the chronicle
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    [HttpPost("{id}/post")]
    public async Task PostPost(int id, Post post)
    {
		post.ChronicleId = id;
		await this.context.Posts.AddAsync(post);

		await this.context.SaveChangesAsync();
    }
}
