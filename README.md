# Microsoft 3D Movie Maker

Released in 1995, this is the original source code to the Microsoft 3D Movie Maker project, now released
under the [MIT license](LICENSE) as open source.

![3D Movie Maker](https://github.com/microsoft/Microsoft-3D-Movie-Maker/blob/main/IMG/3dmovie.jpg?raw=true)

## Building instructions

I managed to make it buildable on my machine with VS 2022 and Windows 11.
Just launch a "Native Tools Command Prompt for VS" and build:
```powershell
.\build.ps1
```
To get it properly working, we need the proper BRender, Audioman and SoftImage libraries, that are currently missing.

## Contributing

The source files in this repo are for historical reference and will be kept static, and this repository will
be archived. Feel free to fork this repo and experiment.

## Code cleanup

This code was restored from the Microsoft corporate archives and cleared for release.

- Developer names and aliases were removed, with the exception of current employees who worked on the
  original release who consented to keeping their names in place
- The archive consisted of several CDs, some of which were for alternate builds or products, and
  have been excluded
- The code does not build with today's engineering tools, and is released as-is.

## Trademarks

This project may contain trademarks or logos for projects, products, or services. Authorized use of Microsoft 
trademarks or logos is subject to and must follow 
[Microsoft's Trademark & Brand Guidelines](https://www.microsoft.com/en-us/legal/intellectualproperty/trademarks/usage/general).
Use of Microsoft trademarks or logos in modified versions of this project must not cause confusion or imply Microsoft sponsorship.
Any use of third-party trademarks or logos are subject to those third-party's policies.

This repo includes a build from 1995 of BRender from Argonaut software. Approval to open source BRender as MIT was given in an email from Jez San, former CEO of Argonaut. Other versions of BRender exist at https://github.com/foone/BRender-v1.3.2 and https://github.com/foone/BRender-1997 Thanks to Jez and the whole BRender team for their hard work on this amazing engine. A full historical list of BRender contributors is available at https://github.com/foone/BRender-v1.3.2/blob/main/README.md 

This repo does NOT include the SoftImage SDK "./DKIT" from 1992.

Jez also offered this interesting BRender anecdote in an email:

```
When Sam Littlewood designed BRender, he didn’t write the code. And then document it.  
The way most things were built at the time.
First, he wrote the manual.  The full documentation
That served as the spec.  Then the coding started.
```


