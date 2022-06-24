using Microsoft.AspNetCore.Mvc;
using PfotenFreunde.Api.Extensions;
using PfotenFreunde.Shared.Contexts;
using PfotenFreunde.Shared.Models;

namespace PfotenFreunde.Api.Controllers;

[ApiController]
[Route("[controller]")]
public class UserController : ControllerBase
{
	private PfotenFreundeContext context;

	public UserController(PfotenFreundeContext context)
	{
		this.context = context;
	}
	
    /// <summary>
    /// Gets all users
    /// </summary>
    [HttpGet]
    public IEnumerable<User> GetAll()
    {
		return this.context.Users;
    }

    /// <summary>
    /// Gets the specified user
    /// </summary>
    [HttpGet("{id}")]
    public async Task<ActionResult<User>> Get(int id)
    {
		var user = await this.context.Users.FindAsync(id);

		if (user == null)
		{
			return NotFound();
		}

		return user;
    }

    /// <summary>
    /// Deletes the specified user
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">User does not exist</response>
    [HttpDelete("{id}")]
    public ActionResult Delete(int id, string reason)
    {
        return this.WithCurrentUser(context, currentUser =>
        {
            var user = this.context.Users.Find(id);

            if (user == null)
            {
                return NotFound();
            }

            if (!this.IsAdministrator() || user.Id != currentUser.Id)
            {
                return Forbid();
            }
            
            this.context.Users.Remove(user);
            
            this.context.SaveChanges();
            
            return Ok();
        });
    }

    /// <summary>
    /// Pauses the subscription of the specified user
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">User does not exist</response>
    [HttpPost("{id}/pause")]
    public async Task<ActionResult> Pause(int id)
    {
        var user = await context.Users.FindAsync(id);
        if (user == null)
        {
            return NotFound();
        }
        
        user.Active = false;
        context.Users.Update(user);
        await context.SaveChangesAsync();

        return Ok();
    }

    /// <summary>
    /// Resumes the subscription of the specified user
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">User does not exist</response>
    [HttpPost("{id}/resume")]
    public async Task<ActionResult> Resume(int id)
    {
        var user = await context.Users.FindAsync(id);
        if (user == null)
        {
            return NotFound();
        }
        
        user.Active = true;
        context.Users.Update(user);
        await context.SaveChangesAsync();

        return Ok();
    }
    
    /// <summary>
    /// Reports the specified user
    /// </summary>
    /// <response code="404">User does not exist</response>
    [HttpPost("{id}/report")]
    public async Task<ActionResult> Report(int id, Report report)
    {
		var user = await this.context.Users.FindAsync(id);
		if (user == null)
		{
			return NotFound();
		}

		report.UserId = id;
		await this.context.Reports.AddAsync(report);
		await this.context.SaveChangesAsync();
		
		return Ok();
    }

    /// <summary>
    /// Locks the user for the specified time in milliseconds
    /// </summary>
    /// <response code="403">Insufficient permissions</response>
    /// <response code="404">User does not exist</response>
    [HttpPost("{id}/lock")]
    public async Task<ActionResult> Lock(int id, ulong time)
    {
        if (!this.IsAdministrator())
        {
            return Forbid();
        }
        
        var user = await context.Users.FindAsync(id);
        if (user == null)
        {
            return NotFound();
        }
        
        user.LockedUntil = DateTime.Now.AddMilliseconds(time);
        context.Users.Update(user);
        await context.SaveChangesAsync();

        return Ok();
    }

    /// <summary>
    /// Gets ratings of user
    /// </summary>
    /// <response code="404">User does not exist</response>
    [HttpGet("{id}/ratings")]
    public IEnumerable<Rating> GetRatings(int id)
    {
        return context.Ratings.Where(x => x.UserId == id);
    }
    
    /// <summary>
    /// Create rating for user
    /// </summary>
    /// <response code="404">User does not exist</response>
    [HttpPost("{id}/ratings")]
    public ActionResult CreateRating(int id, Rating rating)
    {
        return this.WithCurrentUser(context, user =>
        {
            if (context.Users.Find(id) != null)
            {
                return NotFound();
            }
            
            rating.Id = 0;
            rating.SenderId = user.Id;
            rating.UserId = id;
            context.Ratings.Add(rating);
            context.SaveChanges();

            return Ok();
        });
    }

    /// <summary>
    /// Gets pictures of user
    /// </summary>
    [HttpGet("{id}/picture")]
    public IEnumerable<Picture> GetPictures(int id)
    {
        var ids = context.PictureUsers
            .Where(x => x.UserId == id)
            .Select(x => x.Id);
        
        return context.Pictures.Where(x => ids.Contains(x.Id));
    }

    /// <summary>
    /// Uploads picture of user
    /// </summary>
    [HttpPost("{id}/picture")]
    public async Task PostPicture(int id, IFormFile file)
    {
        using var stream = new MemoryStream();
        await file.CopyToAsync(stream);

        var picture = new PictureUser()
        {
            UserId = id,
            Picture = new Picture()
            {
                UploadDate = DateTime.Now,
                Data = stream.ToArray()    
            }
        };
        await context.PictureUsers.AddAsync(picture);
        await context.SaveChangesAsync();
    }

    /// <summary>
    /// Get top users
    /// </summary>
    [HttpGet("top")]
    public IEnumerable<User> GetTop()
    {
        var ids = context.Ratings
            .GroupBy(x => x.UserId)
            .OrderByDescending(x => x.Count())
            .Select(x => x.Key)
            .Take(50);
        return context.Users.Where(x => ids.Contains(x.Id));
    }
}
