#include "types.h"
#include "math.h"
#include "background.h"

// Steps each active BG layer: scroll tween or drift, wobble, zoom bounce and rotation, and
// rebuilds the affine matrix when it changed. Layers with BG_LAYER_COMMIT set are written to the
// scroll registers at the next vblank.
void TickBgLayers(void)
{
    u32 i;
    BgLayer *pLayer;
    u8 angle;
    s16 zoom;
    s32 ref;
    s32 ref2;

    for (i = 0; i < 4; i++)
    {
        pLayer = &g_BgState.aLayers[i];
        if (!(pLayer->dwFlags & (BG_LAYER_TWEEN | BG_LAYER_ROTATE | BG_LAYER_ZOOM_BOUNCE | BG_LAYER_MATRIX_DIRTY)))
            continue;

        if (pLayer->dwFlags & BG_LAYER_TWEEN)
        {
            if (pLayer->wTweenFrames != 0)
            {
                if (pLayer->wTweenFrames == 1)
                {
                    pLayer->scroll.x = pLayer->target.x;
                    pLayer->scroll.y = pLayer->target.y;
                    pLayer->dwFlags &= ~BG_LAYER_TWEEN;
                }
                else
                {
                    pLayer->scroll.x += iwramDivideSignedQuotient(pLayer->target.x - pLayer->scroll.x, pLayer->wTweenFrames);
                    pLayer->scroll.y += iwramDivideSignedQuotient(pLayer->target.y - pLayer->scroll.y, pLayer->wTweenFrames);
                }
                pLayer->wTweenFrames--;
            }
            else
                AddOffsetToPoint(pLayer->step.x, pLayer->step.y, &pLayer->scroll.x);
        }

        pLayer->out.x = pLayer->scroll.x;
        pLayer->out.y = pLayer->scroll.y;
        if (pLayer->dwFlags & BG_LAYER_WOBBLE)
            ApplyBgLayerWobble(i);

        if (pLayer->dwFlags & BG_LAYER_ZOOM_BOUNCE)
        {
            pLayer->wZoom += pLayer->nZoomStep;
            if (pLayer->nZoomStep > 0)
            {
                if ((s16)pLayer->wZoom >= pLayer->nZoomMax)
                {
                    pLayer->wZoom = pLayer->nZoomMax;
                    if (pLayer->nZoomMin != pLayer->nZoomMax)
                        pLayer->nZoomStep = -pLayer->nZoomStep;
                }
            }
            else if (pLayer->nZoomStep < 0)
            {
                if ((s16)pLayer->wZoom <= pLayer->nZoomMin)
                {
                    pLayer->wZoom = pLayer->nZoomMin;
                    if (pLayer->nZoomMin != pLayer->nZoomMax)
                        pLayer->nZoomStep = -pLayer->nZoomStep;
                }
            }
            pLayer->dwFlags |= BG_LAYER_MATRIX_DIRTY;
        }

        if (pLayer->dwFlags & BG_LAYER_ROTATE)
        {
            pLayer->wAngle += pLayer->wAngleStep;
            pLayer->dwFlags |= BG_LAYER_MATRIX_DIRTY;
        }

        if (pLayer->dwFlags & BG_LAYER_MATRIX_DIRTY)
        {
            angle = pLayer->wAngle >> 8;
            zoom = pLayer->wZoom;
            pLayer->nPa = Multiply8_8(Cos8_8(angle), zoom);
            pLayer->nPb = Multiply8_8(Sin8_8(angle), zoom);
            pLayer->nPc = Multiply8_8(-Sin8_8(angle), zoom);
            pLayer->nPd = Multiply8_8(Cos8_8(angle), zoom);
            ref = 0x7800 - pLayer->nPa * 120;
            ref -= pLayer->nCenterX << 8;
            ref -= pLayer->nPb * 80;
            pLayer->nRefX = ref;
            ref2 = 0x5000 - pLayer->nPc * 120;
            ref2 -= pLayer->nCenterY << 8;
            ref2 -= pLayer->nPd * 80;
            pLayer->nRefY = ref2;
            pLayer->dwFlags &= ~BG_LAYER_MATRIX_DIRTY;
        }

        pLayer->dwFlags |= BG_LAYER_COMMIT;
    }
}
