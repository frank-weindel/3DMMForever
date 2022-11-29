/***************************************************************************

    Texture map (br_pixmap wrapper) class

***************************************************************************/
#include "bren.h"

ASSERTNAME

RTCLASS(TMAP)

/***************************************************************************
    A PFNRPO to read TMAP objects.
***************************************************************************/
bool TMAP::FReadTmap(PCRF pcrf, CTG ctg, CNO cno, PBLCK pblck, PBACO *ppbaco, long *pcb)
{
    AssertPo(pcrf, 0);
    AssertPo(pblck, 0);
    AssertNilOrVarMem(ppbaco);
    AssertVarMem(pcb);

    PTMAP ptmap;

    *pcb = pblck->Cb(fTrue);
    if (pvNil == ppbaco)
        return fTrue;
    ptmap = PtmapRead(pcrf->Pcfl(), ctg, cno);
    if (pvNil == ptmap)
    {
        TrashVar(ppbaco);
        TrashVar(pcb);
        return fFalse;
    }
    AssertPo(ptmap, 0);
    *ppbaco = ptmap;
    return fTrue;
}

/***************************************************************************
    Read a TMAP from a chunk
***************************************************************************/
PTMAP TMAP::PtmapRead(PCFL pcfl, CTG ctg, CNO cno)
{
    TMAPF tmapf;
    BLCK blck;
    TMAP *ptmap;
    PGL pglclr = pvNil;
    long cbRowMultiplier = 1;
    void *pixelsFromFile;
    long cbTmapPixels;

    ptmap = NewObj TMAP;
    if (pvNil == ptmap)
        goto LFail;

    if (!pcfl->FFind(ctg, cno, &blck) || !blck.FUnpackData())
        goto LFail;
    if (!blck.FReadRgb(&tmapf, size(TMAPF), 0))
        goto LFail;

    if (kboCur != tmapf.bo)
        SwapBytesBom(&tmapf, kbomTmapf);

    if (tmapf.type == BR_PMT_INDEX_8)
    {
        pglclr = GPT::PglclrGetPalette(); // Current palette
        if (pglclr->IvMac() == 0)
        {
            // Palette does not exist yet (loading shade table)
            // Skip trying to convert this texture
            ReleasePpo(&pglclr);
        }
    }
    Assert(kboCur == tmapf.bo, "bad TMAPF");

    cbTmapPixels = LwMul(tmapf.cbRow, tmapf.dyp);

    ptmap->_bpmp.identifier = (char *)ptmap; // to get TMAP from a (BPMP *)
    if (!FAllocPv((void **)&pixelsFromFile, cbTmapPixels, fmemClear, mprNormal))
    {
        goto LFail;
    }
    ptmap->_bpmp.map = pvNil;
    ptmap->_bpmp.type = tmapf.type;
    ptmap->_bpmp.flags = tmapf.grftmap;
    ptmap->_bpmp.base_x = tmapf.xpLeft;
    ptmap->_bpmp.base_y = tmapf.ypTop;
    ptmap->_bpmp.width = tmapf.dxp;
    ptmap->_bpmp.height = tmapf.dyp;
    ptmap->_bpmp.origin_x = tmapf.xpOrigin;
    ptmap->_bpmp.origin_y = tmapf.ypOrigin;

    if (!blck.FReadRgb(pixelsFromFile, cbTmapPixels, size(TMAPF)))
    {
        goto LFail;
    }

    // If pglclr then TMAP is 8-bit (and the palette exists)
    // Convert to 24-bit
    if (pglclr != pvNil)
    {
        ptmap->_bpmp.type = BR_PMT_RGB_888;
        ptmap->_bpmp.row_bytes = tmapf.cbRow * 3;
        FAllocPv((void **)&ptmap->_bpmp.pixels, cbTmapPixels * 3, fmemClear, mprNormal);
        for (long i = 0; i < cbTmapPixels; i++)
        {
            CLR clr = *(CLR *)(pglclr->QvGet(((byte *)pixelsFromFile)[i]));
            ((byte *)ptmap->_bpmp.pixels)[i * 3] = clr.bBlue;
            ((byte *)ptmap->_bpmp.pixels)[i * 3 + 1] = clr.bGreen;
            ((byte *)ptmap->_bpmp.pixels)[i * 3 + 2] = clr.bRed;
        }

        // No longer need the pixels from file
        FreePpv(&pixelsFromFile);
        ReleasePpo(&pglclr);
    }
    else
    {
        ptmap->_bpmp.row_bytes = tmapf.cbRow;
        ptmap->_bpmp.pixels = pixelsFromFile;
    }
    return ptmap;
LFail:
    ReleasePpo(&ptmap);
    ReleasePpo(&pglclr);
    FreePpv(&pixelsFromFile);
    return pvNil;
}

/***************************************************************************
    Create a TMAP from a BRender BPMP...used only for importing PIX's
***************************************************************************/
PTMAP TMAP::PtmapNewFromBpmp(BPMP *pbpmp)
{
    PTMAP ptmap;

    ptmap = NewObj TMAP;
    if (pvNil == ptmap)
        return pvNil;
    ptmap->_bpmp = *pbpmp;
    ptmap->_bpmp.identifier = (char *)ptmap;
    pbpmp->identifier = (char *)ptmap;
    ptmap->_fImported = fTrue;
    return ptmap;
}

/***************************************************************************
    destructor
***************************************************************************/
TMAP::~TMAP(void)
{
    if (_fImported)
    {
        // REVIEW *****: this crashes BRender...why?
        //		BrMemFree(_bpmp.pixels);
    }
    else
        FreePpv((void **)&_bpmp.pixels);
}

/***************************************************************************
    Write a TMAP to a chunk
***************************************************************************/
bool TMAP::FWrite(PCFL pcfl, CTG ctg, CNO *pcno)
{
    AssertThis(0);
    BLCK blck;

    if (!pcfl->FAdd(size(TMAPF) + LwMul(_bpmp.row_bytes, _bpmp.height), ctg, pcno, &blck))
    {
        return fFalse;
    }

    return FWrite(&blck);
}

/***************************************************************************
    Write a TMAP to the given FLO
***************************************************************************/
bool TMAP::FWrite(PBLCK pblck)
{
    TMAPF tmapf;

    tmapf.bo = kboCur;
    tmapf.osk = koskCur;
    tmapf.cbRow = _bpmp.row_bytes;
    tmapf.type = _bpmp.type;
    tmapf.grftmap = _bpmp.flags;
    tmapf.xpLeft = _bpmp.base_x;
    tmapf.ypTop = _bpmp.base_y;
    tmapf.dxp = _bpmp.width;
    tmapf.dyp = _bpmp.height;
    tmapf.xpOrigin = _bpmp.origin_x;
    tmapf.ypOrigin = _bpmp.origin_y;
    if (!pblck->FWriteRgb(&tmapf, size(TMAPF), 0))
        return fFalse;
    if (!pblck->FWriteRgb(_bpmp.pixels, LwMul(tmapf.cbRow, tmapf.dyp), size(TMAPF)))
    {
        return fFalse;
    }
    return fTrue;
}

#ifdef WIN

#define CALCDIST(bRed1, bGreen1, bBlue1, bRed2, bGreen2, bBlue2)                                                       \
    (((bRed1) - (bRed2)) * ((bRed1) - (bRed2)) + ((bGreen1) - (bGreen2)) * ((bGreen1) - (bGreen2)) +                   \
     ((bBlue1) - (bBlue2)) * ((bBlue1) - (bBlue2)))

/*
 *	PtmapReadNative	--	Creates a TMAP object, reading the data from a .BMP file
 *
 *	input:
 *			pfni	--	the FNI to read the data from
 *			pglclr	--	the colors to map to.
 *
 *	output:
 *			returns the pointer to the new TMAP
 */
PTMAP TMAP::PtmapReadNative(FNI *pfni, PGL pglclr)
{
    byte *prgb = pvNil;
    PTMAP ptmap = pvNil;
    long dxp, dyp;
    bool fUpsideDown;
    long iclrBest, igl;
    long iprgb;
    long dist, min;
    CLR clr, clrSrc;
    PGL pglclrSrc;
    PGL pglCache;

// New Stuff
#pragma pack(2) // the stupid bmfh is an odd number of shorts
    struct BMH
    {
        BITMAPFILEHEADER bmfh;
        BITMAPINFOHEADER bmih;
    };
#pragma pack()
    PFIL pfil;
    RC rc;
    long fpMac, cbBitmap, cbSrc;
    BMH bmh;
    bool fRet;
    FP fpCur = 0;

    AssertPo(pfni, 0);

    if (pvNil == (pfil = FIL::PfilOpen(pfni)))
        goto LFail;

    fpMac = pfil->FpMac();
    if (size(BMH) >= fpMac || !pfil->FReadRgbSeq(&bmh, size(BMH), &fpCur))
        goto LFail;

    cbSrc = bmh.bmih.biSizeImage;

    if (((long)bmh.bmfh.bfSize != fpMac) || bmh.bmfh.bfType != 'MB' || !FIn(bmh.bmfh.bfOffBits, size(BMH), fpMac) ||
        bmh.bmfh.bfReserved1 != 0 || bmh.bmfh.bfReserved2 != 0 || bmh.bmih.biSize != size(bmh.bmih) ||
        bmh.bmih.biPlanes != 1)
    {
        Warn("bad bitmap file");
        goto LFail;
    }

    // if (bmh.bmih.biBitCount != 8)
    // 	{
    // 	Warn("not an 8-bit bitmap");
    // 	goto LFail;
    // 	}

    if (bmh.bmih.biCompression != BI_RGB || cbSrc != fpMac - (long)bmh.bmfh.bfOffBits && (cbSrc != 0))
    {
        Warn("bad compression type or bitmap file is wrong length");
        goto LFail;
    }

    rc.Set(0, 0, bmh.bmih.biWidth, LwAbs(bmh.bmih.biHeight));
    cbBitmap = CbRoundToLong(rc.xpRight) * rc.ypBottom * 3;

    if (rc.FEmpty())
    {
        Warn("Empty bitmap rectangle");
        goto LFail;
    }

    if (!FAllocPv((void **)&prgb, cbBitmap, fmemNil, mprNormal))
        goto LFail;

    if (!pfil->FReadRgb(prgb, cbBitmap, bmh.bmfh.bfOffBits))
    {
        FreePpv((void **)&prgb);
    }

    dxp = bmh.bmih.biWidth;
    dyp = LwAbs(bmh.bmih.biHeight);
    fUpsideDown = bmh.bmih.biHeight < 0;

    if (true) // !!! 24-bit code
    {
        Assert(!fUpsideDown, 0);
        AssertPo(pglclrSrc, 0);
        ptmap = TMAP::PtmapNew(prgb, dxp, dyp, 24);
    }
    else if (false) // !!! 8-bit code
    {
        Assert(!fUpsideDown, 0);
        AssertPo(pglclrSrc, 0);

        if (pglclr != pvNil)
        {
            AssertIn(pglclr->IvMac(), 0, 257);

            //
            // Do a closest color match
            //

            pglCache = GL::PglNew(size(long), pglclrSrc->IvMac());

            if (pglCache != pvNil)
            {

                iclrBest = ivNil;
                for (igl = 0; igl < pglclrSrc->IvMac(); igl++)
                {
                    AssertDo(pglCache->FAdd(&iclrBest), "Ensured by creation");
                }
            }

            for (iprgb = 0; iprgb < (dxp * dyp); iprgb++)
            {

                if (pglCache != pvNil)
                {
                    pglCache->Get(prgb[iprgb], &iclrBest);

                    if (iclrBest != ivNil)
                    {
                        prgb[iprgb] = (BYTE)iclrBest;
                        continue;
                    }
                }

                pglclrSrc->Get(prgb[iprgb], &clrSrc);

                iclrBest = ivNil;
                min = klwMax;

                for (igl = 0; igl < pglclr->IvMac(); igl++)
                {

                    pglclr->Get(igl, &clr);
                    dist = CALCDIST(clrSrc.bRed, clrSrc.bGreen, clrSrc.bBlue, clr.bRed, clr.bGreen, clr.bBlue);

                    if (dist <= min)
                    {
                        min = dist;
                        iclrBest = igl;
                    }
                }

                if (iclrBest != ivNil)
                {
                    AssertIn(iclrBest, 0, pglclr->IvMac());

                    if (pglCache != pvNil)
                    {
                        pglCache->Put(prgb[iprgb], &iclrBest);
                    }

                    prgb[iprgb] = (BYTE)iclrBest;
                }
            }

            ReleasePpo(&pglCache);
        }

        ReleasePpo(&pglclrSrc);

        ptmap = TMAP::PtmapNew(prgb, dxp, dyp);
    }
LFail:
    ReleasePpo(&pfil);
    return ptmap;
}
#endif // WIN

#ifdef MAC
PTMAP TMAP::PtmapReadNative(FNI *pfni)
{
    RawRtn(); // REVIEW peted: NYI
    return pvNil;
}
#endif // MAC

/*
 *	PtmapNew	--	Given pixel data and attributes, creates a new TMAP with
 *		the given information.
 *
 *	input:
 *			prgbPixels	--	the actual pixels for the TMAP
 *			pbmh		--	The bitmap header from the .BMP file
 *
 *	output:
 *			returns the pointer to the new TMAP
 */
PTMAP TMAP::PtmapNew(byte *prgbPixels, long dxp, long dyp, long cBitPixel)
{
    PTMAP ptmap;

    Assert(dxp <= ksuMax, "bitmap too wide");
    Assert(dyp <= ksuMax, "bitmap too high");
    Assert(cBitPixel == 8 || cBitPixel == 24, "invalid cBitPixel");

    if ((ptmap = NewObj TMAP) != pvNil)
    {
        ptmap->_fImported = fFalse;
        ptmap->_bpmp.identifier = (char *)ptmap;
        ptmap->_bpmp.pixels = prgbPixels;
        ptmap->_bpmp.map = pvNil;
        if (cBitPixel == 24)
        {
            ptmap->_bpmp.row_bytes = (br_int_16)dxp * 3;
            ptmap->_bpmp.type = BR_PMT_RGB_888;
        }
        else
        {
            ptmap->_bpmp.row_bytes = (br_int_16)dxp;
            ptmap->_bpmp.type = BR_PMT_INDEX_8;
        }
        ptmap->_bpmp.flags = BR_PMF_LINEAR;
        ptmap->_bpmp.base_x = ptmap->_bpmp.base_y = 0;
        ptmap->_bpmp.width = (br_uint_16)dxp;
        ptmap->_bpmp.height = (br_uint_16)dyp;
        ptmap->_bpmp.origin_x = ptmap->_bpmp.origin_y = 0;
    }
    AssertPo(ptmap, 0);
    return ptmap;
}

/******************************************************************************
    FWriteTmapChkFile
        Writes a stand-alone file with a TMAP chunk in it.  The file can
        be later read in by the CHCM class with the FILE command.

    Arguments:
        PFNI pfniDst   -- FNI indicating the name of the output file
        bool fCompress -- fTrue if the chunk date is to be compressed
        PMSNK pmsnkErr -- optional message sink to direct errors to

    Returns: fTrue if the file was written successfully

************************************************************ PETED ***********/
bool TMAP::FWriteTmapChkFile(PFNI pfniDst, bool fCompress, PMSNK pmsnkErr)
{
    AssertThis(0);
    AssertPo(pfniDst, ffniFile);
    AssertNilOrPo(pmsnkErr, 0);

    bool fRet = fFalse;
    long lwSig;
    PSZ pszErr = pvNil;
    FLO flo;

    if (pvNil == (flo.pfil = FIL::PfilCreate(pfniDst)))
    {
        pszErr = PszLit("Couldn't create destination file\n");
        goto LFail;
    }
    flo.fp = size(long);
    flo.cb = CbOnFile();

    if (fCompress)
    {
        BLCK blck;

        if (!blck.FSetTemp(flo.cb) || !FWrite(&blck))
        {
            pszErr = PszLit("allocation failure\n");
            goto LFail;
        }
        if (!blck.FPackData())
            lwSig = klwSigUnpackedFile;
        else
        {
            lwSig = klwSigPackedFile;
            flo.cb = blck.Cb(fTrue);
        }
        if (!flo.pfil->FWriteRgb(&lwSig, size(long), 0) || !blck.FWriteToFlo(&flo, fTrue))
        {
            pszErr = PszLit("writing to destination file failed\n");
            goto LFail;
        }
    }
    else
    {
        lwSig = klwSigUnpackedFile;
        if (!flo.pfil->FWriteRgb(&lwSig, size(long), 0) || !FWriteFlo(&flo))
        {
            pszErr = PszLit("writing to destination file failed\n");
            goto LFail;
        }
    }

    fRet = fTrue;
LFail:
    if (pszErr != pvNil && pmsnkErr != pvNil)
        pmsnkErr->ReportLine(pszErr);
    if (!fRet && pvNil != flo.pfil)
        flo.pfil->SetTemp();
    ReleasePpo(&flo.pfil);
    return fRet;
}

#ifdef NOT_YET_REVIEWED
byte *TMAP::PrgbBuildInverseTable(void)
{
    byte *prgb, *prgbT, iclr;
    long cbRgb;

    if (_pbpmp->type != BR_PMT_RGB_888)
        return pvNil;

    if (!FAllocPv((void **)&prgb, cbRgb = _pbpmp->height, fmemNil, mprNormal))
        return pvNil;

    for (prgbT = prgb, iclr = 0; iclr < cbRgb; prgbT++, iclr++)
        *prgbT = iclr;

    _SortInverseTable(prgb, cbRgb, BR_COLOUR_RGB(0, 0, 0), BR_COLOUR_RGB(0xFF, 0xFF, 0xFF));
    return prgb;
}

void TMAP::_SortInverseTable(byte *prgb, long cbRgb, BRCLR brclrLo, BRCLR brclrHi)
{
    long cbRgb1 = 0, cbRgb2 = 0;
    byte *prgb2, *prgbRead, bT;
    BRCLR brclrPivot = brclrLo + (brclrHi - brclrLo) / 2;
    BRCLR *pbrclr;

    prgb2 = prgb + cbRgb;
    prgbRead = prgb;
    while (cbRgb--)
    {
        pbrclr = 0; // pbrclr from index *prgb;
        if (*pbrclr <= brclrPivot)
        {
            prgbRead++;
            cbRgb1++;
        }
        else
        {
            bT = *prgb2;
            *--prgb2 = *prgbRead;
            *prgbRead = bT;
            cbRgb2++;
        }
    }
    if (cbRgb1 > 1)
        _SortInverseTable(prgb, cbRgb1, brclrLo, brclrPivot);
    if (cbRgb2 > 1)
        _SortInverseTable(prgb2, cbRgb2, brclrPivot + 1, brclrHi);
}
#endif // NOT_YET_REVIEWED

#ifdef DEBUG
/***************************************************************************
    Assert the validity of the TMAP.
***************************************************************************/
void TMAP::AssertValid(ulong grf)
{
    TMAP_PAR::AssertValid(fobjAllocated);
    if (!_fImported)
        AssertPvCb(_bpmp.pixels, LwMul(_bpmp.row_bytes, _bpmp.height));
}

/***************************************************************************
    Mark memory used by the TMAP.
***************************************************************************/
void TMAP::MarkMem(void)
{
    AssertThis(0);
    TMAP_PAR::MarkMem();
    if (!_fImported)
        MarkPv(_bpmp.pixels);
}
#endif // DEBUG
