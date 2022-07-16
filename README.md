# assfire-router

This repo is a part of the in-development route optimizaton services collection (https://github.com/Eaglegor/assfire-suite).
The intention of this repo is to step out of monorepo development model and move to more flexible model of per-service repo.


This service is intended to be a unified gRPC proxy to different routing providers (like e.g. OSRM) also providing routes caching so that each application that needs routing doesn't implement it's own connectors. It is also intended to allow creating named strategies and transport profiles that define particular routing source and request parameters.


As many of Assfire components, this component may be used as a library ('engine' module) or as a standalone service ('client' and 'server' modules). Both client and engine implement same api ('api' module) for better interchangeability.