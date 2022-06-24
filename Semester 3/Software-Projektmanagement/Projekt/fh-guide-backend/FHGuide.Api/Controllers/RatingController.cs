using Microsoft.AspNetCore.Mvc;
using FHGuide.Shared.Models;
using FHGuide.Shared.Contexts;

namespace FHGuide.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class RatingController : ControllerBase
{
	private readonly FHGuideContext DbContext;

    public RatingController(FHGuideContext dbContext)
    {
		this.DbContext = dbContext;
    }

	/// <summary>
	/// Get all ratings
	/// </summary>
	[HttpGet]
	public IEnumerable<Rating> Get()
	{
		return this.DbContext.Ratings;
	}

	/// <summary>
	/// Create new rating
	/// </summary>
	[HttpPost]
	public async Task<int> Post(Rating rating)
	{
		rating.RatingId = 0;
        var entry = await this.DbContext.Ratings.AddAsync(rating);
        await this.DbContext.SaveChangesAsync();
        return entry.Entity.RatingId;
	}

	/// <summary>
	/// Update rating with specified id
	/// </summary>
	[HttpPatch("{id}")]
	public async Task<ActionResult> Patch(int id, Rating rating)
	{
		if (!this.DbContext.Ratings.Any(x => x.RatingId == id)) {
            return NotFound();
        }
        rating.RatingId = id;
        var entry = this.DbContext.Ratings.Update(rating);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}

	/// <summary>
	/// Delete rating with specified id
	/// </summary>
	[HttpDelete("{id}")]
	public async Task<ActionResult> Delete(int id)
	{
		var rating = await this.DbContext.Ratings.FindAsync(id);
        if (rating == null)
        {
            return NotFound();
        }    
        
        this.DbContext.Ratings.Remove(rating);
        await this.DbContext.SaveChangesAsync();
        return Ok();
	}
}
