using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class RoadmapItemController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public RoadmapItemController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all roadmap items
	/// </summary>
	[HttpGet]
	public IEnumerable<RoadmapItem> Get()
	{
        return this.DbContext.Roadmapitems;
	}

	/// <summary>
	/// Create a new roadmap item
	/// </summary>
	[HttpPost]
	public async Task<int> Post(RoadmapItem roadmapItem)
	{
        roadmapItem.RoadmapItemId = 0;
        
        var entry = await this.DbContext.Roadmapitems.AddAsync(roadmapItem);
        await this.DbContext.SaveChangesAsync();

        return entry.Entity.RoadmapItemId;
	}

	/// <summary>
	/// Update roadmap item with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task Patch(int id, RoadmapItem roadmapItem)
	{
        roadmapItem.RoadmapItemId = id;
        this.DbContext.Roadmapitems.Update(roadmapItem);
        await this.DbContext.SaveChangesAsync();
        
	}

	/// <summary>
	/// Delete roadmap item with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
		var item = await this.DbContext.Roadmapitems.FindAsync(id);

		if (item == null)
		{
			return NotFound();
		}

		this.DbContext.Roadmapitems.Remove(item);
        await this.DbContext.SaveChangesAsync();
		return Ok();
	}
}
